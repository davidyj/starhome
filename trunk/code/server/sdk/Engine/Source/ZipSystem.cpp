#include "../stdafx.h"
#include "ZipSystem.h"
#ifdef _WIN32
#include <string.h>
#else
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#endif


BOOL IsExit(char* filename)
{
	FILE* f;
	f = fopen(filename,"rb");
	if (f == NULL)
	{
		return FALSE;
	}
	else
		fclose(f);
	return TRUE;
}

#ifdef WIN32	
ULONG GetFileTime(const char* fname,tm_zip* tmzip,ULONG *dt)
{
	int ret = 0;
	{
		FILETIME ftLocal;
		HANDLE hFind;
		WIN32_FIND_DATA  ff32;

		hFind = FindFirstFile(fname,&ff32);
		if (hFind != INVALID_HANDLE_VALUE)
		{
			FileTimeToLocalFileTime(&(ff32.ftLastWriteTime),&ftLocal);
			FileTimeToDosDateTime(&ftLocal,((LPWORD)dt)+1,((LPWORD)dt)+0);
			FindClose(hFind);
			ret = 1;
		}
	}
	return ret;
};
#else
ULONG GetFileTime(const char* fname,tm_zip* tmzip)
{	
	if ((!fname) || (!tmzip))
		return -1;

	struct stat s;
	if (stat(fname, &s) < 0){
#ifdef _DEBUG
		printf("failed to stat file %s, in src file %s line %d\n", fname, __FILE__, __LINE__);
#endif		
		return -1;
	}	
	struct  tm *t = localtime(&(s.st_mtime));
	tmzip->tm_sec = t->tm_sec;	
	tmzip->tm_min = t->tm_min;
	tmzip->tm_hour = t->tm_hour;
	tmzip->tm_mday = t->tm_mday;
	tmzip->tm_mon = t->tm_mon;
	tmzip->tm_year = t->tm_year;
}
#endif

int GetFileCrc(const char* filenameinzip, void* buf, unsigned long size_buf, unsigned long* result_crc)
{
	unsigned long calculate_crc = 0;
	int err = ZIP_OK;
	FILE * fin = fopen(filenameinzip,"rb");
	unsigned long size_read = 0;
	unsigned long total_read = 0;
	if (fin==NULL)
	{
		err = ZIP_ERRNO;
	}

	if (err == ZIP_OK)
	{
		do
		{
			err = ZIP_OK;
			size_read = (int)fread(buf,1,size_buf,fin);
			if (size_read < size_buf)
			{
				if (feof(fin)==0)
				{
					printf("error in reading %s\n",filenameinzip);
					err = ZIP_ERRNO;
				}
			}
			if (size_read>0)
			{
				calculate_crc = crc32(calculate_crc,(const Bytef *)buf,size_read);
			}			
			total_read += size_read;

		} 
		while ((err == ZIP_OK) && (size_read>0));
	}	
	if (fin)
		fclose(fin);

	*result_crc=calculate_crc;
	printf("file %s crc %x\n",filenameinzip,calculate_crc);
	return err;
}

/*
 *XXX: not implemented on UNIX platform	
 */
void change_file_date(char* filename,ULONG dosdate,tm_unz tmu_date)
{
#ifdef WIN32	
	HANDLE hFile;
	FILETIME ftm,ftLocal,ftCreate,ftLastAcc,ftLastWrite;

	hFile = CreateFile(filename,GENERIC_READ | GENERIC_WRITE,
		0,NULL,OPEN_EXISTING,0,NULL);
	GetFileTime(hFile,&ftCreate,&ftLastAcc,&ftLastWrite);
	DosDateTimeToFileTime((WORD)(dosdate>>16),(WORD)dosdate,&ftLocal);
	LocalFileTimeToFileTime(&ftLocal,&ftm);
	SetFileTime(hFile,&ftm,&ftLastAcc,&ftm);
	CloseHandle(hFile);
#else
	printf("this function %s is not impplemented on UNIX platform.\n", __func__);
#endif	
}


/* mymkdir and change_file_date are not 100 % portable
As I don't know well Unix, I wait feedback for the unix portion */

int mymkdir(char* dirname)
{
	int ret=0;
#ifdef WIN32
	ret = mkdir(dirname);
#else
	ret = mkdir(dirname, S_IRWXO);
#endif	
	return ret;
}

int makedir (char* newdir)
{
	char *buffer ;
	char *p;
	int  len = (int)strlen(newdir);

	if (len <= 0)
		return 0;

	buffer = (char*)malloc(len+1);
	strcpy(buffer,newdir);

	if (buffer[len-1] == '/') {
		buffer[len-1] = '\0';
	}
	if (mymkdir(buffer) == 0)
	{
		free(buffer);
		return 1;
	}

	p = buffer+1;
	while (1)
	{
		char hold;

		while(*p && *p != '\\' && *p != '/')
			p++;
		hold = *p;
		*p = 0;
		if ((mymkdir(buffer) == -1) && (errno == ENOENT))
		{
			printf("couldn't create directory %s\n",buffer);
			free(buffer);
			return 0;
		}
		if (hold == 0)
			break;
		*p++ = hold;
	}
	free(buffer);
	return 1;
}

extern BOOL	ZipFile( LPCTSTR szZipName, LPCTSTR szFileToZip,int iOverWrite ,int iCompresssLevel ,LPCTSTR szPassword )
{
	char filename_try[MAXFILENAME+16];
	int zipok;
	int err = 0;

	int size_buf = WRITEBUFFERSIZE;
	void* buf = (void*)malloc(size_buf);
	if (buf == NULL)
	{
		//printf("Error allocating memory\n");
		return ZIP_INTERNALERROR;
	}

	if (szFileToZip==NULL)
		zipok = 0;

	else
	{
		int i,len;
		int dot_found=0;
		zipok = 1 ;
		
		//确定压缩文件名称
		strncpy(filename_try, szZipName, MAXFILENAME-1);
		filename_try[ MAXFILENAME ] = '\0';
		len=(int)strlen(filename_try);
		for (i=0;i<len;i++)
		{
			if (filename_try[i]=='.')
			{
				dot_found = 1;
			}
		}
		if (dot_found==0)
		{
			strcat(filename_try,".zip");
		}

		//确定覆盖还是添加
		if (iOverWrite == 2)
		{
			/* if the file don't exist, we not append file */
			if (!IsExit(filename_try))
			{
				iOverWrite = 1;
			}
		}
		else if (iOverWrite == 0)
		{
			if (IsExit(filename_try))
			{
				iOverWrite = 2;
			}
		}
	}
	

	if (zipok == 1)
	{
		zipFile zf;
		int errclose;
#ifdef USEWIN32IOAPI
		zlib_filefunc_def ffunc;
		fill_win32_filefunc(&ffunc);
		zf = zipOpen2(filename_try,(iOverWrite==2) ? 2 : 0,NULL,&ffunc);
#else
		zf = zipOpen(filename_try,(iOverWrite==2) ? 2 : 0);
#endif

		if (zf == NULL)
		{
			printf("error opening %s\n",filename_try);
			err= ZIP_ERRNO;
		}
		else
			printf("creating %s\n",filename_try);

		FILE * fin = NULL;
		int size_read;
		const char* filenameinzip = szFileToZip;
		zip_fileinfo zi;
		unsigned long crcFile=0;

		zi.tmz_date.tm_sec = zi.tmz_date.tm_min = zi.tmz_date.tm_hour =
			zi.tmz_date.tm_mday = zi.tmz_date.tm_mon = zi.tmz_date.tm_year = 0;
		zi.dosDate = 0;
		zi.internal_fa = 0;
		zi.external_fa = 0;
#ifdef WIN32		
		GetFileTime(filenameinzip,&zi.tmz_date,&zi.dosDate);
#else
		GetFileTime(filenameinzip,&zi.tmz_date);
#endif		

		if ((szPassword != NULL) && (err==ZIP_OK))
		{
			err = GetFileCrc(filenameinzip,buf,size_buf,&crcFile);
		}
		err = zipOpenNewFileInZip3(zf,filenameinzip,&zi,NULL,0,NULL,0,NULL,
			(iCompresssLevel != 0) ? Z_DEFLATED : 0,
			iCompresssLevel,0,
			-MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY,
			szPassword,crcFile);

		if (err != ZIP_OK)
			printf("error in opening %s in zipfile\n",filenameinzip);
		else
		{
			fin = fopen(filenameinzip,"rb");
			if (fin==NULL)
			{
				err=ZIP_ERRNO;
				printf("error in opening %s for reading\n",filenameinzip);
			}
		}

		if (err == ZIP_OK)
		{
			do
			{
				err = ZIP_OK;
				size_read = (int)fread(buf,1,size_buf,fin);
				if (size_read < size_buf)
				{
					if (feof(fin)==0)
					{
						printf("error in reading %s\n",filenameinzip);
						err = ZIP_ERRNO;
					}
				}
				if (size_read>0)
				{
					err = zipWriteInFileInZip (zf,buf,size_read);
					if (err<0)
					{
						printf("error in writing %s in the zipfile\n",filenameinzip);
					}

				}
			} while ((err == ZIP_OK) && (size_read>0));
		}
		if (fin)
			fclose(fin);
		if (err<0)
			err=ZIP_ERRNO;
		else
		{
			err = zipCloseFileInZip(zf);
			if (err!=ZIP_OK)
				printf("error in closing %s in the zipfile\n",filenameinzip);
		}
		errclose = zipClose(zf,NULL);
		if (errclose != ZIP_OK)
			printf("error in closing %s\n",filename_try);
	}
	free(buf);
	return TRUE;
}
extern BOOL	ZipFolder(LPCTSTR szZipName, LPCTSTR szFolder,int iFlag ,int iCompresssLevel ,LPCTSTR szPassword)
{
#ifdef WIN32	
	_finddata_t filestruct;
//	int p =0;
//	int fn =0;
	char szSearch[MAXFILENAME];
	
	strcpy(szSearch,szFolder);
	strcat(szSearch,"/*.*");

	int hnd = _findfirst(szSearch,&filestruct);
	if (hnd ==-1)
	{
		return FALSE;
	}
	do
	{ 	
		char szFullName[MAXFILENAME];
		memset(szFullName, 0, sizeof(szFullName));
		if(strlen(szFolder) > 0)
		{
			sprintf(szFullName , "%s/%s" , szFolder , filestruct.name);
		}
		else
		{
			strcpy(szFullName , filestruct.name);
		}
		if(!(filestruct.attrib & _A_SUBDIR)) // 如果文件属性不是’目录’
		{
			ZipFile(szZipName,szFullName,iFlag,iCompresssLevel,szPassword);			
		}
		else // 发现子目录
		{
			if(strcmp(filestruct.name , "..")!=0 && strcmp(filestruct.name , ".")!=0)
			{
				ZipFolder(szZipName,szFullName,iFlag,iCompresssLevel,szPassword); // 递归调用自身
			}
		}
	}while(!_findnext(hnd , &filestruct)); 
	return TRUE;
#else
	printf("function %s not implemented on UNIX platform.\n", __func__);
#warning ZipFolder() not implemented on UNIX platform 	
#endif	
}

//extern BOOL UnZipOneFile(LPCTSTR szZipName,LPCTSTR szUnzFileName,LPCTSTR szOutFileName,int iOverWrite,LPCTSTR szPassword)
//{
//	char filename_try[MAXFILENAME+16] = "";
//	int i;
//	
//	int opt_overwrite = iOverWrite;
//	char* password = szPassword;
//	char *dirname=NULL;
//	char* zipfilename = szZipName;
//	char* filename_to_extract = szUnzFileName;
//	
//	unzFile uf=NULL;
//
//	if (zipfilename!=NULL)
//	{
//
//#ifdef USEWIN32IOAPI
//		zlib_filefunc_def ffunc;
//#endif
//		strncpy(filename_try, zipfilename,MAXFILENAME-1);
//		filename_try[ MAXFILENAME ] = '\0';
//#ifdef USEWIN32IOAPI
//		fill_win32_filefunc(&ffunc);
//		uf = unzOpen2(zipfilename,&ffunc);
//#else
//		uf = unzOpen(zipfilename);
//#endif
//		if (uf==NULL)
//		{
//			strcat(filename_try,".zip");
//#ifdef USEWIN32IOAPI
//			uf = unzOpen2(filename_try,&ffunc);
//#else
//			uf = unzOpen(filename_try);
//#endif
//		}
//	}
//
//	if (uf==NULL)
//	{
//		printf("Cannot open %s or %s.zip\n",zipfilename,zipfilename);
//		return 1;
//	}
//	printf("%s opened\n",filename_try);
//
//	else if (opt_do_extract==1)
//	{
//		if (opt_extractdir && chdir(dirname)) 
//		{
//			printf("Error changing into %s, aborting\n", dirname);
//			exit(-1);
//		}
//
//		return do_extract_onefile(uf,filename_to_extract,
//			opt_do_extract_withoutpath,opt_overwrite,password);
//
//
//	}
//	unzCloseCurrentFile(uf);
//
//	return 0;
//}
//
//BOOL ExtractCurrentFile(unzFile uf,int iOverWrite,LPCSTR szPassword)
//{
//	char filename_inzip[MAXFILENAME];
//	char* filename_withoutpath;
//	char* p;
//	int err=UNZ_OK;
//	FILE *fout=NULL;
//	void* buf;
//	uInt size_buf;
//
//	unz_file_info file_info;
//	uLong ratio=0;
//	err = unzGetCurrentFileInfo(uf,&file_info,filename_inzip,sizeof(filename_inzip),NULL,0,NULL,0);
//
//	if (err!=UNZ_OK)
//	{
//		printf("error %d with zipfile in unzGetCurrentFileInfo\n",err);
//		return err;
//	}
//
//	size_buf = WRITEBUFFERSIZE;
//	buf = (void*)malloc(size_buf);
//	if (buf==NULL)
//	{
//		printf("Error allocating memory\n");
//		return UNZ_INTERNALERROR;
//	}
//
//	p = filename_withoutpath = filename_inzip;
//	while ((*p) != '\0')
//	{
//		if (((*p)=='/') || ((*p)=='\\'))
//			filename_withoutpath = p+1;
//		p++;
//	}
//
//	if ((*filename_withoutpath)=='\0')
//	{
//		if ((*popt_extract_without_path)==0)
//		{
//			printf("creating directory: %s\n",filename_inzip);
//			mymkdir(filename_inzip);
//		}
//	}
//	else
//	{
//		const char* write_filename;
//		int skip=0;
//
//		if ((*popt_extract_without_path)==0)
//			write_filename = filename_inzip;
//		else
//			write_filename = filename_withoutpath;
//
//		err = unzOpenCurrentFilePassword(uf,password);
//		if (err!=UNZ_OK)
//		{
//			printf("error %d with zipfile in unzOpenCurrentFilePassword\n",err);
//		}
//
//		if (((*popt_overwrite)==0) && (err==UNZ_OK))
//		{
//			char rep=0;
//			FILE* ftestexist;
//			ftestexist = fopen(write_filename,"rb");
//			if (ftestexist!=NULL)
//			{
//				fclose(ftestexist);
//				do
//				{
//					char answer[128];
//					int ret;
//
//					printf("The file %s exists. Overwrite ? [y]es, [n]o, [A]ll: ",write_filename);
//					ret = scanf("%1s",answer);
//					if (ret != 1) 
//					{
//						exit(EXIT_FAILURE);
//					}
//					rep = answer[0] ;
//					if ((rep>='a') && (rep<='z'))
//						rep -= 0x20;
//				}
//				while ((rep!='Y') && (rep!='N') && (rep!='A'));
//			}
//
//			if (rep == 'N')
//				skip = 1;
//
//			if (rep == 'A')
//				*popt_overwrite=1;
//		}
//
//		if ((skip==0) && (err==UNZ_OK))
//		{
//			fout=fopen(write_filename,"wb");
//
//			/* some zipfile don't contain directory alone before file */
//			if ((fout==NULL) && ((*popt_extract_without_path)==0) &&
//				(filename_withoutpath!=(char*)filename_inzip))
//			{
//				char c=*(filename_withoutpath-1);
//				*(filename_withoutpath-1)='\0';
//				makedir(write_filename);
//				*(filename_withoutpath-1)=c;
//				fout=fopen(write_filename,"wb");
//			}
//
//			if (fout==NULL)
//			{
//				printf("error opening %s\n",write_filename);
//			}
//		}
//
//		if (fout!=NULL)
//		{
//			printf(" extracting: %s\n",write_filename);
//
//			do
//			{
//				err = unzReadCurrentFile(uf,buf,size_buf);
//				if (err<0)
//				{
//					printf("error %d with zipfile in unzReadCurrentFile\n",err);
//					break;
//				}
//				if (err>0)
//					if (fwrite(buf,err,1,fout)!=1)
//					{
//						printf("error in writing extracted file\n");
//						err=UNZ_ERRNO;
//						break;
//					}
//			}
//			while (err>0);
//			if (fout)
//				fclose(fout);
//
//			if (err==0)
//				change_file_date(write_filename,file_info.dosDate,
//				file_info.tmu_date);
//		}
//
//		if (err==UNZ_OK)
//		{
//			err = unzCloseCurrentFile (uf);
//			if (err!=UNZ_OK)
//			{
//				printf("error %d with zipfile in unzCloseCurrentFile\n",err);
//			}
//		}
//		else
//			unzCloseCurrentFile(uf); /* don't lose the error */
//	}
//
//	free(buf);
//	return err;
//}



BOOL	ZipBufferToBuffer(byte* outBufeer,ULONG &uOutLen, byte* inBuffer,ULONG uInLen, int iCompressLevel)     // 成功返回 Z_OK
{
	int ret = compress2(outBufeer ,&uOutLen , inBuffer ,uInLen , iCompressLevel);
	return ret;
}

BOOL	UnZipBufferToBuffer(byte* outBufeer,ULONG &uOutLen, byte* inBuffer,ULONG uInLen)
{
	int ret = uncompress(outBufeer,&uOutLen,inBuffer,uInLen);
	return ret;
}


ULONG ComputeComSize(ULONG inSize)
{
	return compressBound(inSize);
}

