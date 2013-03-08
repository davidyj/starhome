using System;
using System.Windows.Forms;
using System.IO;
using System.IO.Compression;
using System.Collections;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.Text;
using System.Globalization;
using System.Security.Cryptography;
using System.Xml;
using System.Runtime.InteropServices;
using Microsoft.DirectX.AudioVideoPlayback;

namespace WZextract
{
	public partial class MainForm : Form
	{
		[STAThread]
		private static void Main()
		{
			Application.EnableVisualStyles();
			Application.SetCompatibleTextRenderingDefault(false);
			Application.Run(new MainForm());
		}
		
		/*********
		CLASSES
		*********/
		class WZ_structure
		{
			public WZ_structure()
			{
				this.wz_files	= new List<wz_file>();
				this.encryption	= new WZ_crypto();
				this.mp3_stream	= null;
				this.audio_path	= "";
				this.img_number	= 0;
				this.has_basewz = false;
				this.index_map	= 0;
			}
			
			public void Clear()
			{
				foreach(wz_file f in this.wz_files) {
					f.bStream.Close();
					f.stream.Close();
				}
				this.wz_files.Clear();
				this.encryption.reset();
				this.mp3_stream	= null;
				this.audio_path	= "";
				this.img_number	= 0;
				this.has_basewz = false;
				this.index_map	= 0;
			}
			
			public void calculate_img_count()
			{
				foreach (wz_file f in this.wz_files) {
					this.img_number += f.img_count;
				}
			}
			
			public List<wz_file>	wz_files;
			public WZ_crypto		encryption;
			public Audio			mp3_stream;
			public string			audio_path;
			public int				img_number;
			public int				index_map;
			public bool				has_basewz;
			
		}
		
		class WZ_crypto
		{
			public WZ_crypto()
			{
				this.crypto			= new AesManaged();
				this.crypto.KeySize	= 256;
				this.crypto.Key		= this.key;
				this.crypto.Mode	= CipherMode.ECB;
				this.memStream		= new MemoryStream();
				this.cryptoStream	= new CryptoStream(memStream, this.crypto.CreateEncryptor(), CryptoStreamMode.Write);
				this.keys_kms		= this.getKeys(this.iv_kms);
				this.cryptoStream.Dispose();
				this.memStream.Dispose();
				this.memStream		= new MemoryStream();
				this.cryptoStream	= new CryptoStream(memStream, this.crypto.CreateEncryptor(), CryptoStreamMode.Write);
				this.keys_gms		= this.getKeys(this.iv_gms);
				this.cryptoStream.Dispose();
				this.memStream.Dispose();
				this.listwz			= false;
				this.enc_type		= enc_unknown;
				this.list			= new List<string>();
			}
			
			byte[] getKeys(byte[] iv)
			{
				byte[]	retKey = new byte[ushort.MaxValue];
				byte[]	input = multiplyBytes(iv, 4, 4);				
				int		retlen = retKey.Length;
	
				for (int i = 0; i < (retlen / 16); i++) {
					cryptoStream.Write(input, 0, 16);
					input = memStream.ToArray();
					Array.Copy(memStream.ToArray(), 0, retKey, (i * 16), 16);
					memStream.Position = 0;
				}
				cryptoStream.Write(input, 0, 16);
				Array.Copy(memStream.ToArray(), 0, retKey, (retlen - 15), 15);
				return retKey;
			}
			
			byte[] multiplyBytes(byte[] iv, int count, int mul)
			{
				int count_mul = count * mul;
				byte[] ret = new byte[count_mul];
				for (int i = 0; i < count_mul; i++) {
					ret[i] = iv[i % count];
				}
				return ret;
			}
			
			public void reset()
			{
				this.encryption_detected	= false;
				this.all_strings_encrypted	= false;
				this.listwz					= false;
				this.enc_type				= WZ_crypto.enc_unknown;
				this.keys					= null;
				this.list.Clear();
			}
			
			public bool list_contains(string name)
			{
				foreach(string list_entry in this.list) {
					if(list_entry.Contains(name)) {
						this.list.Remove(list_entry);
						return true;
					}
				}
				return false;
			}

			public void load_listwz(string path)
            {
                return;
				path += "\\List.wz";
				if(File.Exists(path)) {
					this.listwz					= true;
					FileStream		list_file	= new FileStream(path, FileMode.Open, FileAccess.Read, FileShare.Read);
					BinaryReader	listwz		= new BinaryReader(list_file);
					int				length		= (int)list_file.Length;
					int				len			= 0;
					byte			b			= 0;
					string			folder		= "";
					list_file.Position			+= 4;
					byte			check_for_d	= listwz.ReadByte();
					
					if((char)(check_for_d ^ this.keys_gms[0]) == 'd') {
						this.enc_type	= WZ_crypto.enc_GMS;
						this.keys		= this.keys_gms;
					} else if((char)(check_for_d ^ this.keys_kms[0]) == 'd') {
						this.enc_type	= WZ_crypto.enc_KMS;
						this.keys		= this.keys_kms;
					}
					
					list_file.Position = 0;
					while(list_file.Position < length) {
						len	= listwz.ReadInt32() * 2;
						for(int i = 0; i < len; i+=2) {
							b		= (byte)(listwz.ReadByte() ^ this.keys[i]);
							folder += (char)(b);
							list_file.Position++;
						}
						list_file.Position += 2;
						folder.Replace(".im/", ".img");
						this.list.Add(folder);
						folder = "";
					}
					this.list.Remove("dummy");
				}
			}
			
			public void detect_encryption(wz_file f)
			{
				int				old_off	= (int)f.stream.Position;
				f.stream.Position		= 62;
				packed_int(f);
				f.stream.Position++;
				int				len		= (int)(-f.bStream.ReadSByte());
				byte[]			bytes	= f.bStream.ReadBytes(len);
				StringBuilder	sb		= new StringBuilder();
				
				for(int i = 0; i < len; i++) {
					bytes[i] ^= (byte)(0xAA + i);
					sb.Append((char)bytes[i]);
				}
				
				if(sb.ToString().Contains(".img") || sb.ToString().Contains("Cash")) {
					this.all_strings_encrypted = false;
				} else {
					sb.Remove(0, sb.Length);
					if(this.enc_type != WZ_crypto.enc_unknown) {
						for(int i = 0; i < len; i++) {
							bytes[i] ^= this.keys[i];
							sb.Append((char)bytes[i]);
						}
						if(sb.ToString().Contains(".img") || sb.ToString().Contains("Cash")) { 
							this.all_strings_encrypted	= true;
							this.encryption_detected	= true;
						}
					} else {
						for(int i = 0; i < len; i++) { sb.Append((char)(bytes[i] ^ keys_kms[i])); }
						if(sb.ToString().Contains(".img") || sb.ToString().Contains("Cash")) {
							this.enc_type				= WZ_crypto.enc_KMS;
							this.keys					= this.keys_kms;
							this.all_strings_encrypted	= true;
							this.all_pngs_encrypted		= true;
							this.encryption_detected	= true;
						} else {
							sb.Remove(0, sb.Length);
							for(int i = 0; i < len; i++) { sb.Append((char)(bytes[i] ^ keys_gms[i])); }
							if(sb.ToString().Contains(".img") || sb.ToString().Contains("Cash")){
								this.enc_type				= WZ_crypto.enc_GMS;
								this.keys					= this.keys_gms;
								this.all_strings_encrypted	= true;
								this.all_pngs_encrypted		= true;
								this.encryption_detected	= true;
							}
						}
					}
				}
				
				f.stream.Position = old_off;
			}
			
			public string get_encryption_name()
			{
				string name = "";
				
				switch(this.enc_type) {
					case WZ_crypto.enc_KMS:
						name = "KMS";
						break;
						
					case WZ_crypto.enc_GMS:
						name = "GMS";
						break;
						
					case WZ_crypto.enc_unknown:
						name = "Unknown";
						break;
				}
				
				return this.listwz ? name += " with List.wz" : name += " without List.wz";
			}
			
			public const byte	enc_unknown	= 0;
			public const byte	enc_KMS		= 2;
			public const byte	enc_GMS		= 3;
			
			readonly byte[]	iv_gms	= { 0x4d, 0x23, 0xc7, 0x2b };
			readonly byte[] iv_kms	= { 0xb9, 0x7d, 0x63, 0xe9 };
			readonly byte[] key		= {	0x13, 0x00, 0x00, 0x00,
										0x08, 0x00, 0x00, 0x00,
										0x06, 0x00, 0x00, 0x00,
										0xB4, 0x00, 0x00, 0x00,
										0x1B, 0x00, 0x00, 0x00,
										0x0F, 0x00, 0x00, 0x00,
										0x33, 0x00, 0x00, 0x00,
										0x52, 0x00, 0x00, 0x00 };
			
			byte[]				keys_gms, keys_kms;
			AesManaged			crypto;
			MemoryStream		memStream;
			CryptoStream		cryptoStream;
			
			public bool			encryption_detected		= false;
			public bool			all_strings_encrypted	= false;
			public bool			all_pngs_encrypted		= false;
			public bool			listwz					= false;
			public byte			enc_type				= WZ_crypto.enc_unknown;
			public byte[]		keys;
			public List<string>	list;
		}

		class settings
		{
			public string   wz_file_path;
			public string   pngs_path;
			public string   render_path;
			public string   mp3s_path;
			public bool		resolve_uols;
			public int		language;
		}
		
		class wz_header
		{
			public wz_header(string signature, string copyright, string file_name, int head_size, long data_size, long file_size, int[] c_version_check, uint[] hash_version_check, bool checked_version)
			{
				this.signature		= signature;
				this.copyright		= copyright;
				this.file_name		= file_name;
				this.c_version		= 0;
				this.hash_version	= 0;
				this.head_size		= head_size;
				this.data_size		= data_size;
				this.file_size		= file_size;
				this.c_version_test	= c_version_check;
				this.hash_version_test = hash_version_check;
				this.checked_version = checked_version;
			}
			
			public string	signature;
			public string	copyright;
			public string	file_name;
			public int		c_version;
			public uint		hash_version;
			public int		head_size;
			public long		data_size;
			public long		file_size;
			public int[]	c_version_test;
			public uint[]   hash_version_test;
			public bool		checked_version;

		}
		
		class MP3
		{
			public MP3(int offset, int length, int ms){
				this.offset = offset;
				this.length = length;
				this.ms		= ms;
			}
			
			public int offset;
			public int length;
			public int ms;
		}
		
		class PNG
		{
			public PNG(int w, int h, int data_length, int form, int offs, int wz_f)
			{
				this.w		= w;
				this.h		= h;
				this.data_length = data_length;
				this.form	= form;
				this.offs	= offs;
				this.wz_f	= wz_f;
			}
			
			public int w;
			public int h;
			public int data_length;
			public int form;
			public int offs;
			public int wz_f;
		}
		
		class vector
		{
			public vector(int x, int y)
			{
				this.x = x;
				this.y = y;
			}
			
			public int x;
			public int y;
		}
		
		class UOL
		{
			public UOL(string uol)
			{
				this.uol = uol;	
			}
			
			public string uol;
		}
		
		class image
		{
			//public image(string name, int size, int cs32, int offs, bool extr, bool chec, bool on_list, string wz_f)
			public image(string name, int size, int cs32, int offs, bool extr, bool chec, bool on_list, int wz_f)
			{
				this.name = name;
				this.wz_f = wz_f;
				this.size = size;
				this.cs32 = cs32;
				this.offs = offs;
				this.extr = extr;
				this.chec = chec;
				this.on_list = on_list;
				this.node = new TreeNode(name);
			}
			
			public string	name;
			//public string	wz_f;
			public int		wz_f;
			public int		size;
			public int		cs32;
			public int		offs;
			public bool		extr;
			public bool		chec;
			public bool		on_list;
			public TreeNode	node;
		}
		
		class tile
		{
			public tile(Bitmap pic, int x, int y, int ox, int oy, bool flip){
				this.pic	= pic;
				this.x		= x;
				this.y		= y;
				this.ox		= ox;
				this.oy		= oy;
				this.flip	= flip;
			}
			
			public Bitmap	pic;
			public int		x;
			public int		y;
			public int		ox;
			public int		oy;
			public bool		flip;
		}
		
		class wz_file
		{
			public wz_file(string FileName){
				this.stream		= new FileStream(FileName, FileMode.Open);
				this.bStream	= new BinaryReader(this.stream);
				this.img_count	= 0;
			}
			
			public FileStream	stream;
			public BinaryReader	bStream;
			public wz_header	header;
			public int			img_count;
		}
		
		/********* 
		GLOBALS
		*********/
		settings		pref;
		WZ_structure	WZ		= new WZ_structure();
		bool			is_extr	= false;
		
		/*******************
		BASIC FILE READING
		*******************/
		static int packed_int(wz_file f)
		{
			int s = f.bStream.ReadSByte();
			return (s == -128) ? f.bStream.ReadInt32() : s;
		}
		
		static float packed_float(wz_file f)
		{
			float fl = f.bStream.ReadSByte();
			return (fl == -128) ? f.bStream.ReadSingle() : fl;
		}
		
		string readStrAt(int offset, wz_file f, bool use_enc)
		{
			int	oldoffset		= (int)f.stream.Position;
			f.stream.Position	= offset;
			string	ret			= readStr(f, use_enc);
			f.stream.Position	= oldoffset;
			return	ret;
		}
		
		string readStr(wz_file f, bool use_enc)
		{
			StringBuilder	retStr	= new StringBuilder();
			int				size	= f.bStream.ReadSByte();
			
			if(size < 0) {
				byte	mask = 0xAA;
						size = (size == -128) ? f.bStream.ReadInt32() : -size;
				
				for(int i = 0; i < size; i++) {
					retStr.Append((char)(f.bStream.ReadByte() ^ (use_enc || WZ.encryption.all_strings_encrypted ? mask ^ WZ.encryption.keys[i] : mask)));
					unchecked { mask++; } 
				}
				return retStr.ToString();
			}
			
			if(size > 0) {
				int mask = 0xAAAA;
				if (size == 127) { size = f.bStream.ReadInt32(); }

				for(int i = 0; i < size; i++) {
					retStr.Append((char) (f.bStream.ReadByte() + f.bStream.ReadByte()*0x100 ^ (use_enc || WZ.encryption.all_strings_encrypted ? mask ^ WZ.encryption.keys[2*i] ^ (WZ.encryption.keys[2*i+1]*0x100) : mask)));
					unchecked { mask++; }
				}
				return retStr.ToString();
			}
			
			return "";
		}
		
		string get_string(int offset, wz_file f, bool use_enc)
		{
			switch(f.bStream.ReadByte()) {
				case 0x00:
					return readStr(f, use_enc);
					
				case 0x01:
					return readStrAt(offset + f.bStream.ReadInt32(), f, use_enc);
					
				case 0x04:
					f.stream.Position += 8;
					return "";
					
				case 0x73:
					goto case 0x00;
					
				case 0x1B:
					goto case 0x01;
					
				default:
					MessageBox.Show("Unknown string type at offset: " + Convert.ToString(f.stream.Position, CultureInfo.InvariantCulture), "Error", MessageBoxButtons.OK, MessageBoxIcon.Error, MessageBoxDefaultButton.Button1, 0);
					break;
			}
			return "";
		}

		wz_header get_header(string filename, wz_file f)
		{
			string signature = new string(f.bStream.ReadChars(4));
			
			if(signature != "PKG1"){ return null; }

			int		filesize	= (int)f.stream.Length;
			int		datasize	= (int)f.bStream.ReadInt64();
			int		headersize	= f.bStream.ReadInt32();
			string	copyright	= new string(f.bStream.ReadChars(headersize - (int)f.stream.Position));
			int	 	encver		= f.bStream.ReadUInt16();

			int[]   ver		 = new int[5];
			uint[]  h_ver	   = new uint[5];

			int start_ver = -1;
			for (int i = 0; i < 5; i++) {
				ver[i] = get_version(encver, start_ver);
				h_ver[i] = get_version_hash(encver, ver[i]);
				start_ver = ver[i];
			}
			
			wz_header header = new wz_header(signature, copyright, filename, headersize, datasize, filesize, ver, h_ver, false);
			return header;
		}

		int get_version(int encver, int start_version)
		{
			int		sum;
			string	versionStr;
			int a = 0, b = 0, c = 0, d = 0, e = 0, i = start_version, l = 0;
			
			do {
				i++;
				sum = 0;
				versionStr = i.ToString(CultureInfo.InvariantCulture);
				l = versionStr.Length;
				for(int j = 0; j < l; j++) {
					sum <<= 5;
					sum += (int)versionStr[j] + 1;
				}
				a = (sum >> 24) & 0xFF;
				b = (sum >> 16) & 0xFF;
				c = (sum >> 08) & 0xFF;
				d = sum & 0xFF;
				e = 0xFF ^ a ^ b ^ c ^ d;
			} while(e != encver);
 
			return i;
		}
		
		uint get_version_hash(int encver, int realver)
		{
			int		EncryptedVersionNumber	= encver; 
			int		VersionNumber			= realver;
			int		VersionHash				= 0;
			int		DecryptedVersionNumber	= 0;
			int		a = 0, b = 0, c = 0, d = 0, l = 0;
			string	VersionNumberStr;
			
			VersionNumberStr = VersionNumber.ToString(CultureInfo.InvariantCulture);
			
			l = VersionNumberStr.Length;
			for(int i = 0; i < l; i++) {
				VersionHash = (32 * VersionHash) + (int)VersionNumberStr[i] + 1;
			}
			a = (VersionHash >> 24) & 0xFF;
			b = (VersionHash >> 16) & 0xFF;
			c = (VersionHash >> 08) & 0xFF;
			d = VersionHash & 0xFF;
			DecryptedVersionNumber = 0xFF ^ a ^ b ^ c ^ d;
			
			return (EncryptedVersionNumber == DecryptedVersionNumber) ? Convert.ToUInt32(VersionHash) : 0;
		}

		void get_DirTree(TreeNode parent, wz_file f, string fPath, byte enc_type, bool all_on_list_child)
		{
			List<string>	dirs	= new List<string>();
			string			name	= "";
			int				size	= 0;
			int				cs32	= 0;
			int				offs	= 0;
			int				count	= packed_int(f);
			bool			on_list	= false;
			bool			use_enc	= !WZ.encryption.listwz ? true : false;
			bool			all_lst	= (all_on_list_child || WZ.encryption.list.Contains(parent.Text.ToLower() + '/')) ? true : false;
			
			for(int i = 0; i < count; i++) {
				switch(f.bStream.ReadByte()) {
					case 0x02:
						name = readStrAt(f.header.head_size + 1 + f.bStream.ReadInt32(), f, use_enc);
						size = packed_int(f);
						cs32 = packed_int(f);
						offs = calc_offset(f);
						on_list = (all_lst || ((parent.Text == "Base.wz" || parent.Text == "base.wz") && WZ.encryption.list_contains(name.ToLower())) || WZ.encryption.list_contains(parent.Text.ToLower().Replace(".wz", "") + '/' + name.ToLower())) ? true : false ;
						parent.Nodes.Add(name).Tag = new image(name, size, cs32, offs, false, false, on_list, WZ.wz_files.IndexOf(f));
						f.img_count++;
						break;
						
					case 0x03:
						name = readStr(f, use_enc);
						size = packed_int(f);
						cs32 = packed_int(f);
						f.stream.Position += 4;
						dirs.Add(name);
						break;
						
					case 0x04:
						name = readStr(f, use_enc);
						size = packed_int(f);
						cs32 = packed_int(f);
						offs = calc_offset(f);
						on_list = (all_lst || ( (parent.Text == "Base.wz" || parent.Text == "base.wz") && WZ.encryption.list_contains(name.ToLower()) ) || WZ.encryption.list_contains(parent.Text.ToLower().Replace(".wz", "") + '/' + name.ToLower())) ? true : false ;
						parent.Nodes.Add(name).Tag = new image(name, size, cs32, offs, false, false, on_list, WZ.wz_files.IndexOf(f));
						f.img_count++;
						break;
				}
			}

			foreach(string dir in dirs) {
				TreeNode t = parent.Nodes.Add(dir);
				t.Tag = "";
				if(f.header.file_name == "Base.wz" || f.header.file_name == "base.wz") {
					WZ.has_basewz = true;
					get_DirTree(t, f, fPath, enc_type, false);
					load_file(fPath + "\\" + dir + ".wz", t);
				} else { get_DirTree(t, f, fPath, enc_type, all_lst); }
			}
		}

		int calc_offset(wz_file f)
		{
			uint	offset		= (uint)(f.stream.Position - 0x3C) ^ 0xFFFFFFFF;
			uint	bytes		= f.bStream.ReadUInt32();
			int		distance	= 0;
			long	pos			= f.stream.Position;
			uint[]	test_offset	= new uint[5];

			if (!f.header.checked_version)	{
				for (int i = 0; i < 5; i++) {
					test_offset[i]	=	offset * System.Convert.ToUInt32(f.header.hash_version_test[i]);
					test_offset[i]	-=	0x581C3F6D;
					distance		=	(int)test_offset[i] & 0x1F;
					test_offset[i]	=	(test_offset[i] << distance) | (test_offset[i] >> (32 - distance));
					test_offset[i]	^=	bytes;
					test_offset[i]	+=	0x78;

					if (test_offset[i] < f.header.file_size) {
						f.stream.Position = test_offset[i];
						if (f.stream.ReadByte() == 0x73) {
							f.stream.Position = pos;
							f.header.c_version = f.header.c_version_test[i];
							f.header.hash_version = f.header.hash_version_test[i];
							f.header.checked_version = true;
							offset = test_offset[i];
							i = 5;
						}
					}
				}
			} else {
				offset		*=	f.header.hash_version;
				offset		-=	0x581C3F6D;
				distance	=	(int)offset & 0x1F;
				offset		=	(offset << distance) | (offset >> (32 - distance));
				offset		^=	bytes;
				offset		+=	0x78;
			}
			return (int)offset;
		}
		
		void load_file(string filename, TreeNode parent)
		{
			string fName = Path.GetFileName(filename);
			string fPath = Path.GetDirectoryName(filename);
			wz_file f;

			try {
				f = new wz_file(filename);
				if(!WZ.encryption.encryption_detected){ WZ.encryption.detect_encryption(f); }
			} catch {
				Cursor = Cursors.Default;
				toolStripStatusLabel1.Text = "Error!";
				treeView1.Enabled = true;
				menuStrip1.Enabled = true;
				MessageBox.Show("Error: " + fName + " could not be opened! Maybe it's used by another program already.", "Error while opening " + fName, MessageBoxButtons.OK, MessageBoxIcon.Error, MessageBoxDefaultButton.Button1, 0);
				mnuHeaderInfo.Enabled = false;
				return;
			}

			f.header = get_header(fName, f);
			if (f.header == null) {
				treeView1.Enabled = true;
				menuStrip1.Enabled = true;
				toolStripStatusLabel1.Text = "Error!";
				Cursor = Cursors.Default;
				MessageBox.Show("Wrong file signature in " + fName + "!", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error, MessageBoxDefaultButton.Button1, 0);
				mnuHeaderInfo.Enabled = false;
				return;
			}
			
			WZ.wz_files.Add(f);
			if(fName.ToLower() == "map.wz") {
				WZ.index_map = WZ.wz_files.IndexOf(f);;
			}
			get_DirTree(parent, f, fPath, WZ.encryption.enc_type, false);
		}
		
		bool check_if_extracted(image img)
		{
			if(!img.extr) {
				wz_file w			= WZ.wz_files[img.wz_f];
				w.stream.Position	= img.offs;
				if(!img.chec) {
					int cs = 0;
					for(int i = 0; i < img.size; i++) {
						cs += w.stream.ReadByte();
					}
					if(cs != img.cs32) {
						MessageBox.Show("Checksum test failed! You could run into problems when running MapleStory with this file!", "Integrity Check failed");
						return false;
					}
					img.chec			= true;
					w.stream.Position	= img.offs;
				}
				extract_img(img.offs, img.node, 0, w, img.on_list);
				img.extr				= true;
			}
			return true;
		}
		
		/*************
		EXTRACTING
		*************/
		void extract_value(int offset, TreeNode parent, wz_file f, bool use_enc)
		{
			parent = parent.Nodes.Add(get_string(offset, f, use_enc));
			switch(f.bStream.ReadByte()){
				case 0x00:
					parent.Tag = null;
					break;
					
				case 0x02:
					parent.Tag = f.bStream.ReadInt16();
					break;
					
				case 0x03:
					parent.Tag = packed_int(f);
					break;
					
				case 0x04:
					parent.Tag = packed_float(f);
					break;
					
				case 0x05:
					parent.Tag = f.bStream.ReadDouble();
					break;
					
				case 0x08:
					parent.Tag = get_string(offset, f, use_enc);
					break;
					
				case 0x09:
					extract_img(offset, parent, f.bStream.ReadInt32() + (int)f.stream.Position, f, use_enc);
					break;
					
				case 0x0B:
					parent.Tag = f.bStream.ReadInt16();
					break;
					
				default:
					MessageBox.Show("Error in get_value. Offset: " + Convert.ToString(f.stream.Position, CultureInfo.InvariantCulture), "Error", MessageBoxButtons.OK, MessageBoxIcon.Error, MessageBoxDefaultButton.Button1, 0);
					break;
			}
		}
		
		void extract_img(int offset, TreeNode parent, int eob, wz_file f, bool is_on_list)
		{
			int entries = 0;

			switch(get_string(offset, f, is_on_list)) {
				case "Property":
					f.stream.Position += 2;
					entries = packed_int(f);
					for(int i = 0; i < entries; i++) {
						extract_value(offset, parent, f, is_on_list);
					}
					break;
					
				case "Shape2D#Vector2D":
					parent.Tag = new vector(packed_int(f), packed_int(f));
					break;
					
				case "Canvas":
					f.stream.Position++;
					if(f.bStream.ReadByte() == 0x01) {
						f.stream.Position += 2;
						entries = packed_int(f);
						for(int i = 0; i < entries; i++) { extract_value(offset, parent, f, is_on_list); }
					}
					int w		= packed_int(f);
					int h		= packed_int(f);
					int form	= packed_int(f) + f.bStream.ReadByte();
					f.stream.Position += 4;
					int bufsize	= f.bStream.ReadInt32();
					//parent.Tag = new PNG(w, h, bufsize-1, form, (int)f.stream.Position+1, f.header.file_name);
					parent.Tag = new PNG(w, h, bufsize-1, form, (int)f.stream.Position+1, WZ.wz_files.IndexOf(f));
					f.stream.Position += bufsize;
					break;
					
				case "Shape2D#Convex2D":
					entries = packed_int(f);
					for(int i = 0; i < entries; i++) { extract_img(offset, parent, 0, f, is_on_list); }
					break;
					
				case "Sound_DX8":
					f.stream.Position++;
					int len				= packed_int(f);
					int ms				= packed_int(f);
					parent.Tag			= new MP3(eob - len, len, ms);
					f.stream.Position	= eob;
					break;
					
				case "UOL":
					f.stream.Position++;
					parent.Tag = new UOL(get_string(offset, f, is_on_list));
					break;
					
				default:
					break;
			}			
		}
	
		Bitmap extract_png(PNG png, wz_file f)
		{
			DeflateStream		zlib;
			int					size_png = 0;
			int					x = 0, y = 0, b = 0, g = 0;
			Bitmap				png_decoded = null;
			BitmapData			bmp_data;
			byte[]				plain_data;
			f.stream.Position	= png.offs;
			
			if(f.bStream.ReadUInt16() == 0x9C78) {
				zlib = new DeflateStream(f.stream, CompressionMode.Decompress);
			} else {
				f.stream.Position -= 2;
				MemoryStream	data_stream		= new MemoryStream();
				int				blocksize		= 0;
				int				end_of_png		= (int)(png.data_length + f.stream.Position);
				
				while(f.stream.Position < end_of_png){
					blocksize = f.bStream.ReadInt32();
					for(int i = 0; i < blocksize; i++) {
						data_stream.WriteByte((byte)(f.bStream.ReadByte() ^ WZ.encryption.keys[i]));
					}
				}
				data_stream.Position	= 2;
				zlib					= new DeflateStream(data_stream, CompressionMode.Decompress);
			}

			switch (png.form) {
				case 1:
					png_decoded	= new Bitmap(png.w, png.h, PixelFormat.Format32bppArgb);
					bmp_data	= png_decoded.LockBits(new Rectangle(0, 0, png.w, png.h), ImageLockMode.WriteOnly, PixelFormat.Format32bppArgb);
					size_png	= png.w * png.h * 2;
					plain_data	= new byte[size_png];
					zlib.Read(plain_data, 0, size_png);
					byte[] argb = new Byte[size_png * 2];
					for (int i = 0; i < size_png; i++) {
						b = plain_data[i] & 0x0F; b |= (b << 4); argb[i * 2] = (byte)b;
						g = plain_data[i] & 0xF0; g |= (g >> 4); argb[i * 2 + 1] = (byte)g;
					}
					Marshal.Copy(argb, 0, bmp_data.Scan0, argb.Length);
					png_decoded.UnlockBits(bmp_data);
					break;

				case 2:
					png_decoded	= new Bitmap(png.w, png.h, PixelFormat.Format32bppArgb);
					bmp_data	= png_decoded.LockBits(new Rectangle(0, 0, png.w, png.h), ImageLockMode.WriteOnly, PixelFormat.Format32bppArgb);
					size_png	= png.w * png.h * 4;
					plain_data	= new byte[size_png];
					zlib.Read(plain_data, 0, size_png);
					Marshal.Copy(plain_data, 0, bmp_data.Scan0, plain_data.Length);
					png_decoded.UnlockBits(bmp_data);
					break;

				case 513:
					png_decoded	= new Bitmap(png.w, png.h, PixelFormat.Format16bppRgb565);
					bmp_data	= png_decoded.LockBits(new Rectangle(0, 0, png.w, png.h), ImageLockMode.WriteOnly, PixelFormat.Format16bppRgb565);
					size_png	= png.w * png.h * 2;
					plain_data	= new byte[size_png];
					zlib.Read(plain_data, 0, size_png);
					Marshal.Copy(plain_data, 0, bmp_data.Scan0, plain_data.Length);
					png_decoded.UnlockBits(bmp_data);
					break;

				case 517:
					png_decoded	= new Bitmap(png.w, png.h);
					size_png	= png.w * png.h / 128;
					plain_data	= new byte[size_png];
					zlib.Read(plain_data, 0, size_png);
					byte iB = 0;
					for (int i = 0; i < size_png; i++) {
						for (byte j = 0; j < 8; j++) {
							iB = Convert.ToByte(((plain_data[i] & (0x01 << (7 - j))) >> (7 - j)) * 0xFF);
							for (int k = 0; k < 16; k++) {
								if (x == png.w) { x = 0; y++; }
								png_decoded.SetPixel(x, y, Color.FromArgb(0xFF, iB, iB, iB));
								x++;
							}
						}
					}
					break;
			}
			
			return png_decoded;
		}
		
		void saveMP3(MP3 mp3, string filename, wz_file f)
		{
			FileStream	save	= new FileStream(filename, FileMode.OpenOrCreate);
			f.stream.Position	= mp3.offset;
			save.Write(f.bStream.ReadBytes(mp3.length), 0, mp3.length);
			save.Close();
		}
		
		void full_extract_img(image img, TreeNode node, string path)
		{			
			foreach(TreeNode child in node.Nodes) {
				StringBuilder name = new StringBuilder(path);
				name.Append(child.Text);
				if(child.Tag == null) { full_extract_img(img, child, name.Append(".").ToString()); continue; }
				
				switch(child.Tag.GetType().Name) {
					case "PNG":
						name.Append(".png");
						name.Replace(":", "_", 3, name.Length-3);
						Directory.CreateDirectory(Path.GetDirectoryName(name.ToString()));
						extract_png((PNG)child.Tag, WZ.wz_files[img.wz_f]).Save(name.ToString());
						break;
						
					case "MP3":
						name.Append(".mp3");
						name.Replace(":", "_", 3, name.Length-3);
						saveMP3((MP3)child.Tag, name.ToString(), WZ.wz_files[img.wz_f]);
						break;
						
					default:
						full_extract_img(img, child, name.Append('.').ToString());
						break;
				}
			}
		}
		
		void full_extract(TreeNode parent, string path, ref int count)
		{
			if(is_extr){
				foreach(TreeNode node in parent.Nodes) {
					DirectoryInfo	di = Directory.CreateDirectory(path + node.Text + "\\");
	
					if(node.Tag.GetType().Name == "image") {
						count++;
						image img = (image)node.Tag;
						if(check_if_extracted(img)) {
							full_extract_img(img, img.node, di.FullName);
							img.extr = false;
							img.node.Nodes.Clear();
						}
						StringBuilder position = new StringBuilder(Convert.ToString(count));
						position.Append("/");
						position.Append(Convert.ToString(WZ.img_number));
						position.Append(" img's extracted");
						extractBar.Value = count;
						extractCount.Text = position.ToString();
						Application.DoEvents();
					} else { full_extract(node, di.FullName, ref count); }
				}
			}
		}
		
		/*************
		MAP RENDERER
		*************/ 
		bool render_map(image map_img, wz_file f)
		{
			Application.DoEvents();
			
			int map_width = 0, map_height = 0, map_centerX = 0, map_centerY = 0;
			List<Bitmap> layers = new List<Bitmap>();
			TreeNode found_node;
			image t_img;

			toolStripStatusLabel1.Text = "Getting map size...";
			try {
				map_width	= (int)get_value("miniMap\\width",		map_img);
				map_height	= (int)get_value("miniMap\\height",		map_img);
				map_centerX	= (int)get_value("miniMap\\centerX",	map_img);
				map_centerY	= (int)get_value("miniMap\\centerY", 	map_img);
			} catch {
				int map_top = 0, map_bottom = 0, map_left = 0, map_right = 0;

				try {
					map_top		= (int)get_value("info\\VRTop",		map_img);
					map_bottom	= (int)get_value("info\\VRBottom",	map_img);
					map_left	= (int)get_value("info\\VRLeft",	map_img);
					map_right	= (int)get_value("info\\VRRight",	map_img);

					map_width	= map_right		- map_left;
					map_height	= map_bottom	- map_top;
					map_centerX	= -map_left;
					map_centerY	= -map_top;
				} catch {
					MessageBox.Show("Sorry, but this map cannot be rendered due to size information lacking. Maybe this map might be rendered in the future.", "Impossible to render this map", MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
					return false;
				}
			}
			
			foreach (TreeNode n in map_img.node.Nodes) {
				if ("0123456789".IndexOf(n.Text.Substring(0), 0) != -1) {
					layers.Add(render_layer(n, map_height, map_width, map_centerX, map_centerY, f, map_img));
					Application.DoEvents();
				}
			}

			Bitmap		finalMap	= new Bitmap(map_width, map_height);
			Graphics	fMap		= Graphics.FromImage(finalMap);

			toolStripStatusLabel1.Text = "Creating picture...";
			switch (lstRenders.SelectedIndex) {
				case 0:
					fMap.FillRectangle(Brushes.Transparent, 0, 0, map_width, map_height);
					break;
					
				case 1:
					fMap.FillRectangle(Brushes.Black, 0, 0, map_width, map_height);
					break;
					
				case 2:
					fMap.FillRectangle(Brushes.White, 0, 0, map_width, map_height);
					break;
			}
					
			foreach (Bitmap bmp in layers) { fMap.DrawImage(bmp, 0, 0); }

			//Portals
			if (chkPortalr.Checked == true) {
				toolStripStatusLabel1.Text = "Adding portals";
				TreeNode portals = FindNode(map_img.node, "portal");

				if (portals != null) {
					image	MapHelper		= FindImage("Map\\MapHelper.img", treeView1.Nodes[0]);
					Bitmap	portal_picture	= extract_png((PNG)get_value("portal\\game\\pv\\0", MapHelper), f);
					foreach (TreeNode node in portals.Nodes) {
						if ((int)FindNode(node, "pt").Tag == 2 && Convert.ToString(FindNode(node, "pn").Tag).Substring(0, 2) != "in") {
							fMap.DrawImage(portal_picture, (int)FindNode(node, "x").Tag + map_centerX - 43, (int)FindNode(node, "y").Tag + map_centerY - 173);
						}
						Application.DoEvents();
					}
				}
			}

			//Reactors
			if (chkReactorr.Checked == true) {
				toolStripStatusLabel1.Text = "Adding reactors";
				TreeNode reactors = FindNode(map_img.node, "reactor");
				if (reactors != null) {
					if (reactors.Nodes.Count > 0){
						foreach (TreeNode reactor in reactors.Nodes){
							found_node = FindNode(reactor, "id");
							if (found_node != null){
								t_img = FindImage("Reactor\\" + (string)found_node.Tag + ".img", treeView1.Nodes[0]);
								if (t_img != null){
									string link = (string)get_value("info\\link", t_img);
									if (link != null){
										t_img = FindImage("Reactor\\" + link + ".img", treeView1.Nodes[0]);
									}

									vector v = (vector)get_value("0\\0\\origin", t_img);
									bool flip = Convert.ToBoolean(FindNode(reactor, "f").Tag);
									if (!flip){
										fMap.DrawImage(extract_png((PNG)get_value("0\\0", t_img), WZ.wz_files[t_img.wz_f]), (int)FindNode(reactor, "x").Tag + map_centerX - v.x, (int)FindNode(reactor, "y").Tag + map_centerY - v.y);
									}else{
										Bitmap flippedBmp = extract_png((PNG)get_value("0\\0", t_img), WZ.wz_files[t_img.wz_f]);
										flippedBmp.RotateFlip(RotateFlipType.RotateNoneFlipX);
										fMap.DrawImage(flippedBmp, (int)FindNode(reactor, "x").Tag + map_centerX + v.x - flippedBmp.Width, (int)FindNode(reactor, "y").Tag + map_centerY - v.y);
									}
									Application.DoEvents();
								}
							}
						}
					}
				}
			}

			//Monsters
			if (chkMobr.Checked == true) {
				toolStripStatusLabel1.Text = "Adding monsters...";
				TreeNode monsters = FindNode(map_img.node, "life");
				if (monsters != null) {
					if (monsters.Nodes.Count > 0) {
						string stand_fly = "stand";
						foreach (TreeNode life in monsters.Nodes) {
							if ((string)FindNode(life, "type").Tag == "m") {
								t_img = FindImage("Mob\\" + (string)FindNode(life, "id").Tag + ".img", treeView1.Nodes[0]);
								string link = (string)get_value("info\\link", t_img);
								while(link != null) {
									t_img = FindImage("Mob\\" + link + ".img", treeView1.Nodes[0]);
									link = (string)get_value("info\\link", t_img);
								}
				 
								if (FindNode(t_img.node, "stand") == null){ stand_fly = "fly"; }

								vector	v		= (vector)get_value(stand_fly + "\\0\\origin", t_img);
								bool	flip	= Convert.ToBoolean(FindNode(life, "f").Tag);

								if (!flip) {
									object mob_picture = get_value(stand_fly + "\\0", t_img);
									if (mob_picture != null) {
										PNG png_mob;
										if (mob_picture.GetType().Name == "UOL") {
											TreeNode uol_node = FindNode(FindNode(t_img.node, stand_fly), "0");
											png_mob = (PNG)(resolve_UOL((UOL)mob_picture, uol_node).Tag);
											TreeNode resolved_node = resolve_UOL((UOL)mob_picture, uol_node);
											resolved_node = FindNode(resolved_node, "origin");

											v = (vector)resolved_node.Tag;
										}
										else { png_mob = (PNG)mob_picture; }
										Bitmap bitmap_mob = extract_png(png_mob, WZ.wz_files[t_img.wz_f]);
										int x_mob = (int)FindNode(life, "x").Tag + map_centerX - v.x;
										int y_mob = (int)FindNode(life, "cy").Tag + map_centerY - v.y;
										fMap.DrawImage(bitmap_mob, x_mob, y_mob);
									}
								}
								else
								{
									object mob_picture = get_value(stand_fly + "\\0", t_img);

									if (mob_picture != null)
									{
										PNG png_mob;
										if (mob_picture.GetType().Name == "UOL") {
											TreeNode uol_node = FindNode(FindNode(t_img.node, stand_fly), "0");
											png_mob = (PNG)(resolve_UOL((UOL)mob_picture, uol_node).Tag);
											TreeNode resolved_node = resolve_UOL((UOL)mob_picture, uol_node);
											resolved_node = FindNode(resolved_node, "origin");
											v = (vector)resolved_node.Tag;
										} else { png_mob = (PNG)mob_picture; }
										
										Bitmap flippedBmp = extract_png(png_mob, WZ.wz_files[t_img.wz_f]);
										flippedBmp.RotateFlip(RotateFlipType.RotateNoneFlipX);
										fMap.DrawImage(flippedBmp, (int)FindNode(life, "x").Tag + map_centerX + v.x - flippedBmp.Width, (int)FindNode(life, "cy").Tag + map_centerY - v.y);
									}
								}
							} else { continue; }
							Application.DoEvents();
						}
					}
				}
			}

			//NPC
			if (chkNPCr.Checked == true) {
				toolStripStatusLabel1.Text = "Adding NPCs...";
				TreeNode npcs = FindNode(map_img.node, "life");
				if (npcs != null) {
					if (npcs.Nodes.Count > 0) {
						foreach (TreeNode life in npcs.Nodes) {
							if ((string)FindNode(life, "type").Tag == "n") {
								t_img		= FindImage("Npc\\" + (string)FindNode(life, "id").Tag + ".img", treeView1.Nodes[0]);
								vector v	= (vector)get_value("stand\\0\\origin", t_img);
								found_node	= FindNode(life, "f");

								if (found_node != null) {
									bool flip = Convert.ToBoolean(FindNode(life, "f").Tag);
									if (!flip) {
										object npc_picture = get_value("stand\\0", t_img);
										if (npc_picture != null) {
											PNG png_npc;
											if (npc_picture.GetType().Name == "UOL") {
												TreeNode uol_node = FindNode(FindNode(t_img.node, "stand"), "0");
												png_npc = (PNG)(resolve_UOL((UOL)npc_picture, uol_node).Tag);
												TreeNode resolved_node = resolve_UOL((UOL)npc_picture, uol_node);
												resolved_node = FindNode(resolved_node, "origin");
												v = (vector)resolved_node.Tag;
											} else { png_npc = (PNG)npc_picture; }

											fMap.DrawImage(extract_png(png_npc, WZ.wz_files[t_img.wz_f]), (int)FindNode(life, "x").Tag + map_centerX - v.x, (int)FindNode(life, "cy").Tag + map_centerY - v.y);
										}
									} else {
										object npc_picture = get_value("stand\\0", t_img);
										if (npc_picture != null) {
											PNG png_npc;
											if (npc_picture.GetType().Name == "UOL") {
												TreeNode uol_node = FindNode(FindNode(t_img.node, "stand"), "0");
												png_npc = (PNG)(resolve_UOL((UOL)npc_picture, uol_node).Tag);
												TreeNode resolved_node = resolve_UOL((UOL)npc_picture, uol_node);
												resolved_node = FindNode(resolved_node, "origin");
												v = (vector)resolved_node.Tag;
											} else { png_npc = (PNG)npc_picture; }

											Bitmap flippedBmp = extract_png(png_npc, WZ.wz_files[t_img.wz_f]);
											flippedBmp.RotateFlip(RotateFlipType.RotateNoneFlipX);
											fMap.DrawImage(flippedBmp, (int)FindNode(life, "x").Tag + map_centerX + v.x - flippedBmp.Width, (int)FindNode(life, "cy").Tag + map_centerY - v.y);
										}
									}
								} else {
									fMap.DrawImage(extract_png((PNG)get_value("stand\\0", t_img), WZ.wz_files[t_img.wz_f]), (int)FindNode(life, "x").Tag + map_centerX - v.x, (int)FindNode(life, "cy").Tag + map_centerY - v.y);
								}
							} else { continue; }
							Application.DoEvents();
						}
					}
				}
			}
			
			toolStripStatusLabel1.Text = "Ending process...";
			picRender.Image	= finalMap;
			picRender.Size	= finalMap.Size;
			return true;
		}

		Bitmap render_layer(TreeNode layer_node, int height, int width, int centerX, int centerY, wz_file f, image map_img)
		{
			TreeNode t_node, t_node2;
			int x = 0, y = 0, z = 0, i = 0;
			vector v		= new vector(0, 0);
			bool flipped	= false;
			SortedList<int, List<tile>> z_layer_objects	= new SortedList<int, List<tile>>();
			SortedList<int, List<tile>> z_layer_tiles	= new SortedList<int, List<tile>>();
			Bitmap bMap		= new Bitmap(width, height);
			Graphics gMap	= Graphics.FromImage(bMap);
			image tile_img, obj_img;
			string tS_tile	= "";
			TreeNode		found_node;
			
			toolStripStatusLabel1.Text = "Getting Objects...";
			
			t_node = FindNode(layer_node, "obj");
			for (i = 0; i < t_node.Nodes.Count; i++) {
				t_node2 = FindNode(t_node, i.ToString());

				if (t_node2 != null) {
					found_node		= FindNode(t_node2, "x"); if (found_node != null) { x = (int)found_node.Tag; }
					found_node		= FindNode(t_node2, "y"); if (found_node != null) { y = (int)found_node.Tag; }
					found_node		= FindNode(t_node2, "z"); if (found_node != null) { z = (int)found_node.Tag; }
					found_node		= FindNode(t_node2, "f"); if (found_node != null) { flipped = System.Convert.ToBoolean(found_node.Tag); }
					string oS_obj	= (string)(FindNode(t_node2, "oS").Tag);
					string l0_obj	= (string)(FindNode(t_node2, "l0").Tag);
					string l1_obj	= (string)(FindNode(t_node2, "l1").Tag);
					string l2_obj	= (string)(FindNode(t_node2, "l2").Tag);

					obj_img			= FindImage("Map\\Obj\\" + oS_obj + ".img",treeView1.Nodes[0]);
					object png_uol	= get_value(l0_obj + "\\" + l1_obj + "\\" + l2_obj + "\\0", obj_img);

					PNG png;
					if (png_uol.GetType().Name == "UOL") {
						MessageBox.Show("UOL obj");
						TreeNode uol_node		= FindNode(FindNode(FindNode(FindNode(obj_img.node, l0_obj), l1_obj), l2_obj), "0");
						png						= (PNG)resolve_UOL((UOL)png_uol, uol_node).Tag;
					}
					else { png = (PNG)png_uol; }
					
					found_node	= FindByFullPath(l0_obj + "\\" + l1_obj + "\\" + l2_obj + "\\0", obj_img.node);
					found_node	= FindNode(found_node, "origin"); if (found_node != null) { v = (vector)found_node.Tag; }

					if (z_layer_objects.ContainsKey(z)) {
						z_layer_objects[z].Add(new tile(extract_png(png, f), x, y, v.x, v.y, flipped));
					} else {
						z_layer_objects.Add(z, new List<tile>());
						z_layer_objects[z].Add(new tile(extract_png(png, f), x, y, v.x, v.y, flipped));
					}
				}
			}

			toolStripStatusLabel1.Text = "Getting Tiles...";
			t_node = FindNode(layer_node, "info");
			if (t_node.Nodes.Count > 0) { tS_tile = (string)(FindNode(t_node, "tS").Tag); }

			t_node = FindNode(layer_node, "tile");
			if ((t_node.Nodes.Count > 0)) {
				for (i = 0; i < t_node.Nodes.Count; i++) {
					t_node2 = FindNode(t_node, i.ToString());
					if (t_node2 != null) {
						found_node	= FindNode(t_node2, "x");	if (found_node != null) { x = (int)found_node.Tag; }
						found_node	= FindNode(t_node2, "y");	if (found_node != null) { y = (int)found_node.Tag; }
						found_node	= FindNode(t_node2, "zM");	if (found_node != null) { z = (int)found_node.Tag; }

						string u_tile = "", no_tile = "";

						found_node	= FindNode(t_node2, "u");	if (found_node != null) { u_tile	= (string)(found_node.Tag); } 
						found_node	= FindNode(t_node2, "no");	if (found_node != null) { no_tile	= found_node.Tag.ToString();}

						tile_img	= FindImage("Map\\Tile\\" + tS_tile + ".img", treeView1.Nodes[0]);
						PNG png		= (PNG)get_value(u_tile + "\\" + no_tile, tile_img);
						found_node	= FindByFullPath(u_tile + "\\" + no_tile , tile_img.node);
						found_node 	= FindNode(found_node, "origin"); if (found_node != null) { v = (vector)found_node.Tag; } 

						found_node	= FindByFullPath(u_tile + "\\" + no_tile, tile_img.node);
						found_node 	= FindNode(found_node, "z");
						if (found_node != null) { z += (int)found_node.Tag; }

						if (z_layer_tiles.ContainsKey(z)) {
							z_layer_tiles[z].Add(new tile(extract_png(png, f), x, y, v.x, v.y, flipped));
						} else {
							z_layer_tiles.Add(z, new List<tile>());
							z_layer_tiles[z].Add(new tile(extract_png(png, f), x, y, v.x, v.y, flipped));
						}
					}
				}
			}

			toolStripStatusLabel1.Text = "Adding Objects";
			foreach (KeyValuePair<int, List<tile>> z_layer in z_layer_objects) {
				foreach (tile t in z_layer.Value) {
					if (!t.flip) {
						gMap.DrawImage(t.pic, t.x + centerX - t.ox, t.y + centerY - t.oy);
					} else {
						Bitmap flippedBmp = t.pic;
						flippedBmp.RotateFlip(RotateFlipType.RotateNoneFlipX);
						gMap.DrawImage(flippedBmp, t.x + centerX + t.ox - flippedBmp.Width, t.y + centerY - t.oy);
					}
				}
			}

			toolStripStatusLabel1.Text = "Adding Tiles...";
			foreach (KeyValuePair<int, List<tile>> z_layer in z_layer_tiles) {
				foreach (tile t in z_layer.Value) {
					if (!t.flip) {
						gMap.DrawImage(t.pic, t.x + centerX - t.ox, t.y + centerY - t.oy);
					} else {
						Bitmap flippedBmp = t.pic;
						flippedBmp.RotateFlip(RotateFlipType.RotateNoneFlipX);
						gMap.DrawImage(flippedBmp, t.x + centerX + t.ox - flippedBmp.Width, t.y + centerY - t.oy);
					}
				}
			}

			return bMap;
		}

		/*******************
		DATA TREE ROUTINES
		*******************/
		TreeNode FindNode(TreeNode treeNode, string searchFor)
		{
			foreach(TreeNode n in treeNode.Nodes) {
				if(n.Text == searchFor){ return n; }
			}
			return null;
		}
		
		TreeNode FindByFullPath(string path, TreeNode node)
		{
			string[] sPath = path.Split('\\');
			foreach(string s in sPath) {
				node = FindNode(node, s);
				if(node == null) { return null; }
			}
			return node;
		}
		
		object get_value(string path, image img)
		{
			TreeNode result = FindByFullPath(path, img.node);
			if (result == null) { return null; }
			else { return result.Tag; }
		}
		
		image FindImage(string path, TreeNode node)
		{
			string[] sPath = path.Split('\\');
			foreach(string s in sPath) {
				node = FindNode(node, s);
				if(node == null) { return null; }
			}
			if(check_if_extracted((image)node.Tag)) { return (image)node.Tag; }
			else { return null; }
		}
		
		bool SearchTree(TreeNode treeNode, string searchFor)
		{
			if(treeNode.Text.IndexOf(searchFor) > -1)
			{
				treeView1.SelectedNode = treeNode;
				return true;
			}
			foreach (TreeNode tn in treeNode.Nodes)
			{
				if (SearchTree(tn,searchFor)) {
					return true;
				}
			}
			return false;
		}
		
		TreeNode resolve_UOL(UOL u, TreeNode node)
		{
			string[] dirs	= u.uol.Split('/');
			node			= node.Parent;
			foreach(string dir in dirs){
				switch (dir) {
					case "":
						break;

					case "..":
						node = node.Parent;
						break;

					default:
						node = FindNode(node, dir);
						break;
				}
			}
			
			object tag = node.Tag;
			if(tag.GetType().Name == "UOL") {
				node = resolve_UOL((UOL)tag, node);
			}
			return node;
		}
		
		/*************
		GUI RELATED
		**************/
		public MainForm()
		{
			InitializeComponent();
		}
		
		void clear()
		{			
			WZ.Clear();
			txtType.Clear();
			textBox8.Clear();
			textBox8.Visible = false;
			pictureBox1.Visible = false;
			toolStripStatusLabel1.Text = "";
			treeView1.Nodes.Clear();
			treeView2.Nodes.Clear();
		}
		
		void Load_XML_Preferences()
		{
			// Loading preferences from XML file
			pref = new settings();
			string str_xml = Application.StartupPath + "\\WZextract_settings.xml";

			// We have to check if the file exists or else it will crash
			if (File.Exists(str_xml) == true)
			{
				XmlReader XML = XmlReader.Create(str_xml);

				XML.Read();
				XML.ReadStartElement("Settings");
				XML.ReadStartElement("WZ_Files"); pref.wz_file_path = XML.ReadString(); XML.ReadEndElement();
				XML.ReadStartElement("PNGs"); pref.pngs_path = XML.ReadString(); XML.ReadEndElement();
				XML.ReadStartElement("Map_Renders"); pref.render_path = XML.ReadString(); XML.ReadEndElement();
				XML.ReadStartElement("MP3s"); pref.mp3s_path = XML.ReadString(); XML.ReadEndElement();
				XML.ReadStartElement("Resolve_UOLs"); pref.resolve_uols = XML.ReadContentAsBoolean(); XML.ReadEndElement();
				XML.ReadStartElement("Language"); pref.language = XML.ReadContentAsInt(); XML.ReadEndElement();
				XML.Close();

				if (pref.wz_file_path	== "None") { pref.wz_file_path	= ""; }
				if (pref.pngs_path		== "None") { pref.pngs_path		= ""; }
				if (pref.render_path	== "None") { pref.render_path	= ""; }
				if (pref.mp3s_path		== "None") { pref.mp3s_path		= ""; }
			}
			else
			{
				// File not existing so we create a new one with default options
				XmlWriter XML = new XmlTextWriter(str_xml, Encoding.Default);
				XML.WriteStartDocument();
					XML.WriteStartElement("Settings");
						XML.WriteStartElement("WZ_Files");
							XML.WriteString("None"); pref.wz_file_path = "";
						XML.WriteEndElement();
						XML.WriteStartElement("PNGs");
							XML.WriteString("None"); pref.pngs_path = "";
						XML.WriteEndElement();
						XML.WriteStartElement("Map_Renders");
							XML.WriteString("None"); pref.render_path = "";
						XML.WriteEndElement();
						XML.WriteStartElement("MP3s");
							XML.WriteString("None"); pref.mp3s_path = "";
						XML.WriteEndElement();
						XML.WriteStartElement("Resolve_UOLs");
							XML.WriteValue(false); pref.resolve_uols = false;
						XML.WriteEndElement();
						XML.WriteStartElement("Language");
							XML.WriteValue(0); pref.language = 0;
						XML.WriteEndElement();
					XML.WriteEndElement();
				XML.WriteEndDocument();
				XML.Close();
			}
		}
		
		void handle_controls(byte number)
		{			
			switch(number) {
				case 1: //deactivate all
					label9.Visible		= false;
					pnlPicture.Visible  = false;
					button2.Visible		= false;
					chkPortal.Visible	= false;
					chkReactor.Visible	= false;
					chkMob.Visible		= false;
					chkNPC.Visible		= false;
					lstRender.Visible	= false;
					textBox8.Visible	= false;
					lblUOL.Visible		= false;
					pnlSound.Visible	= false;
					button1.Visible		= false;
					button6.Visible		= false;
					
					if(WZ.mp3_stream != null){
						timer1.Stop();
						WZ.mp3_stream.Dispose();
						File.Delete(WZ.audio_path);
						button3.Enabled = true;
						button4.Enabled = false;
						button4.Text	= "Pause";
						button5.Enabled	= false;
						trackBar1.Value = 0;
					}
					break;
					
				case 2: //img selected
					label9.Visible		= false;
					pnlPicture.Visible  = false;
					lblUOL.Visible		= false;
					textBox8.Visible	= true;
					button1.Visible		= true;
					button6.Visible		= true;
					break;
					
				case 3:	//img selected/map				
					button2.Visible		= true;
					chkPortal.Visible	= true;
					chkReactor.Visible	= true;
					chkMob.Visible		= true;
					chkNPC.Visible		= true;
					lstRender.Visible	= true;
					goto case 2;
					
				case 4: //MP3 selected
					pnlSound.Visible	= true;
					button1.Visible		= true;
					button6.Visible		= true;
					break;
					
				case 5: //PNG selected
					pnlPicture.Visible	= true;
					pictureBox1.Enabled = true;
					pictureBox1.Visible	= true;
					label9.Visible		= true;
					button1.Visible		= true;
					button6.Visible		= true;
					break;
					
				case 6: //vector selected
					goto case 2;
					
				case 7: //UOL selected
					lblUOL.Visible		= true;
					button1.Visible		= true;
					button6.Visible		= true;
					break;

				default:
					goto case 1;
			}
		}
		
		void QuitToolStripMenuItemClick(object sender, EventArgs e)
		{
			Application.Exit();
		}

		void OpenToolStripMenuItemClick(object sender, EventArgs e)
		{
			OpenFileDialog dlgOpen	= new OpenFileDialog();
			dlgOpen.Title			= "Select the WZ file...";
			dlgOpen.Filter			= "MapleStory Base.wz file|*.wz";
			if (pref.wz_file_path != "") { dlgOpen.InitialDirectory = pref.wz_file_path; }
			
			DialogResult	dlgresult	= dlgOpen.ShowDialog();
			string			filename	= dlgOpen.FileName;
			
			if (dlgresult == DialogResult.OK) {
				int		run_time	= Environment.TickCount;
				Cursor				= Cursors.WaitCursor;
				toolStripStatusLabel1.Text = "Loading the filetree may take a while. Please be patient !";
				label1.Visible		= false;
				treeView1.Enabled	= false;
				menuStrip1.Enabled	= false;
				treeView1.BeginUpdate();
				clear();
				handle_controls(1);
				TreeNode t			= new TreeNode(Path.GetFileName(filename));
				WZ.encryption.load_listwz(Path.GetDirectoryName(filename));
				
				if (Path.GetFileName(filename).ToLower() != "list.wz") {
					load_file(filename, t);
					mnuHeaderInfo.Enabled	= true;
					mnuWZCompare.Enabled	= true;
					mnuSaveXML.Enabled		= true;
					mnuLoadXML.Enabled		= true;
					mnuExtract.Enabled		= true;
				} else {
					textBox8.Visible		= false;
					string tmp_str			= "";
					
					foreach (string f in WZ.encryption.list) {
						tmp_str += f + "\r\n";
					}
					
					textBox8.Text			= tmp_str;
					textBox8.Visible		= true;
					mnuHeaderInfo.Enabled	= false;
					mnuWZCompare.Enabled	= false;
					mnuSaveXML.Enabled		= false;
					mnuLoadXML.Enabled		= false;
					mnuExtract.Enabled		= false;
				}
				
				t.Expand();
				treeView1.Nodes.Add(t);
				treeView1.Sort();
				treeView1.EndUpdate();
				treeView1.Enabled	= true;
				menuStrip1.Enabled	= true;
				toolStripStatusLabel1.Text = "File structure successfully loaded. Needed " + Convert.ToString(Environment.TickCount - run_time, CultureInfo.InvariantCulture) + " ms.";
				WZ.calculate_img_count();
				toolStripStatusLabel2.Text = "Number of img files: " + Convert.ToString(WZ.img_number, CultureInfo.InvariantCulture);
				Cursor = Cursors.Default;
				dlgOpen.Dispose();
			}
			GC.Collect();
		}

		void TreeView1AfterSelect(object sender, TreeViewEventArgs e)
		{
			treeView2.Nodes.Clear();
			TreeNode sn		= treeView1.SelectedNode;
			object	t_img_d = sn.Tag;
			
			if (t_img_d != null) {
				string type = t_img_d.GetType().Name;
				handle_controls(1);

				if (type == "image")
				{
					txtType.Text = type;
					image t_img = (image)t_img_d;
					if (!t_img.extr)
					{
						Cursor = Cursors.WaitCursor;
						int run_time = Environment.TickCount;
						toolStripStatusLabel1.Text = "Extracting the img file may take a while. Please be patient!";
						menuStrip1.Enabled = false;
						treeView1.Enabled = false;
						treeView2.Enabled = false;
						if (check_if_extracted(t_img)) {
							toolStripStatusLabel1.Text = "img file successfully extracted. Needed " + Convert.ToString(Environment.TickCount - run_time, CultureInfo.InvariantCulture) + " ms.";
						} else {
							toolStripStatusLabel1.Text = "Error while extracting img.";
							return;
						}
						treeView1.Enabled = true;
						menuStrip1.Enabled = true;
						Cursor = Cursors.Default;
					}

					textBox8.Clear();
					textBox8.AppendText("Name\t" + t_img.name + "\r\n");
					textBox8.AppendText("Size\t" + Convert.ToString(t_img.size, CultureInfo.InvariantCulture) + "\r\n");
					textBox8.AppendText("CS32\t" + Convert.ToString(t_img.cs32, CultureInfo.InvariantCulture) + "\r\n");
					textBox8.AppendText("Offs\t" + Convert.ToString(t_img.offs, CultureInfo.InvariantCulture) + "\r\n");
					textBox8.AppendText("List\t" + Convert.ToString(t_img.on_list));

					if (((sn.Parent.Text.Length > 3) && (sn.Parent.Text.Substring(0, 3) == "Map")) || (sn.Text == "MapLogin.img")) {
						handle_controls(3);	}
					else { handle_controls(2); }

					treeView2.BeginUpdate();
					treeView2.Nodes.Clear();
					treeView2.Nodes.Add(t_img.node);
					treeView2.Nodes[0].Expand();
					treeView2.EndUpdate();
					treeView2.Enabled = true;
				} else { txtType.Text = "folder"; }
			}
		}
		
		void TreeView2AfterSelect(object sender, TreeViewEventArgs e)
		{
			string type		= "[This entry is empty]";
			object t_img_d	= null;
			if(treeView2.SelectedNode.Tag != null) {
				t_img_d	= treeView2.SelectedNode.Tag;
				type	= t_img_d.GetType().Name;
			}
			txtType.Text		= type;
			handle_controls(1);
			
			switch(type) {					
				case "PNG":
					pictureBox1.Image	= extract_png((PNG)t_img_d, WZ.wz_files[((PNG)t_img_d).wz_f]);
					pictureBox1.Size	= pictureBox1.Image.Size;
					handle_controls(5);
					break;
					
				case "MP3":
					MP3			mp3		= (MP3)t_img_d;
					TimeSpan	time	= TimeSpan.FromMilliseconds(mp3.ms);
					textBox1.Text		= "Duration: " + Convert.ToString(time.TotalMilliseconds) + " ms \r\nOffset:   " + Convert.ToString(mp3.offset) + "\r\nLength:   " + Convert.ToString(mp3.length) + " Bytes";
					label3.Text			= Convert.ToString(time.Minutes).PadLeft(2, '0') + ":" + Convert.ToString(time.Seconds).PadLeft(2, '0');
					handle_controls(4);
					break;
				
				case "vector":
					vector vt			= (vector)t_img_d;
					textBox8.Text		= "x: " + vt.x + "\r\ny: " + vt.y;
					handle_controls(6);
					break;
					
				case "UOL":
					if (!pref.resolve_uols) {
						lblUOL.Text			= ((UOL)t_img_d).uol;
						handle_controls(7);
					} else {
						treeView2.SelectedNode = resolve_UOL((UOL)t_img_d, treeView2.SelectedNode);
					}
					break;
					
				default:
					textBox8.Text = Convert.ToString(t_img_d);
					handle_controls(2);
					break;
			}
		}

		void PictureBox1Click(object sender, EventArgs e)
		{
			SaveFileDialog dlgSave	= new SaveFileDialog();
			dlgSave.Title			= "Save picture as PNG";
			dlgSave.Filter			= "PNG image|*.png|GIF image|*.gif|BMP image|*.bmp|JPG image|*.jpg";
			dlgSave.FileName		= treeView2.SelectedNode.Text;
			if (pref.pngs_path != "") { dlgSave.InitialDirectory = pref.pngs_path; }
			if(dlgSave.ShowDialog() == DialogResult.OK)
			{
				switch(dlgSave.FilterIndex)
				{
					case 1:
						pictureBox1.Image.Save(dlgSave.FileName, ImageFormat.Png);
						break;
					case 2:
						pictureBox1.Image.Save(dlgSave.FileName, ImageFormat.Gif);
						break;
					case 3:
						pictureBox1.Image.Save(dlgSave.FileName, ImageFormat.Bmp);
						break;
					case 4:
						pictureBox1.Image.Save(dlgSave.FileName, ImageFormat.Jpeg);
						break;
					default:
						pictureBox1.Image.Save(dlgSave.FileName, ImageFormat.Png);
						break;
				}
			}
			dlgSave.Dispose();
		}
		
		void BtnSaveMp3Click(object sender, EventArgs e)
		{
			SaveFileDialog dlgSave	= new SaveFileDialog();
			dlgSave.Title			= "Save MP3";
			dlgSave.Filter			= "MP3 file|*.mp3";
			dlgSave.FileName		+= treeView2.SelectedNode.Text;
			if (pref.mp3s_path != "") { dlgSave.InitialDirectory = pref.mp3s_path; }
			MP3 mp3					= (MP3)treeView2.SelectedNode.Tag;
			
			if(dlgSave.ShowDialog() == DialogResult.OK) {
				saveMP3(mp3, dlgSave.FileName, WZ.wz_files[((image)treeView1.SelectedNode.Tag).wz_f]);
			}
			dlgSave.Dispose();
		}
		
		void Button2Click(object sender, EventArgs e)
		{
			if(!WZ.has_basewz)
			{
				MessageBox.Show("Map rendering is only possible when Base.wz was opened", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error, MessageBoxDefaultButton.Button1, 0);
				return;
			}
			
			int run_time			= Environment.TickCount;
			toolStripStatusLabel1.Text	= "Rendering the map may take a while. Please be patient!";
			treeView1.Enabled		= false;
			button2.Enabled			= false;
			chkPortal.Enabled		= false;
			chkReactor.Enabled		= false;
			chkMob.Enabled			= false;
			chkNPC.Enabled			= false;
			lstRender.Visible		= false;
			menuStrip1.Enabled		= false;
			renderContainer.Dock	= DockStyle.Fill;
			picRender.Image			= null;
			renderContainer.Visible	= true;
			mnuFile.Visible			= false;
			mnuExtras.Visible		= false;
			mnuAbout.Visible		= false;
			mnuCloseRender.Visible	= true;

			if(render_map((image)treeView1.SelectedNode.Tag, WZ.wz_files[WZ.index_map]))
			{
				treeView1.Enabled		= true;
				menuStrip1.Enabled		= true;	
				button2.Enabled			= true;
				chkPortal.Enabled		= true;
				chkReactor.Enabled		= true;
				chkMob.Enabled			= true;
				chkNPC.Enabled			= true;
				lstRender.Visible		= true;
				GC.Collect();
				toolStripStatusLabel1.Text	= "Map successfully rendered. Needed " + Convert.ToString(Environment.TickCount - run_time, CultureInfo.InvariantCulture) + " ms.";
			}
			else
			{
				treeView1.Enabled		= true;
				menuStrip1.Enabled		= true;	
				button2.Enabled			= true;
				chkPortal.Enabled		= true;
				chkReactor.Enabled		= true;
				chkMob.Enabled			= true;
				chkNPC.Enabled			= true;
				lstRender.Visible		= true;
				renderContainer.Visible	= false;
				mnuFile.Visible			= true;
				mnuExtras.Visible		= true;
				mnuAbout.Visible		= true;
				mnuCloseRender.Visible	= false;
				toolStripStatusLabel1.Text	= "Error while rendering!";
			}
		}
		
		void ShowHeaderInformationToolStripMenuItemClick(object sender, EventArgs e)
		{
			if(WZ.wz_files.Count > 0) {
				StringBuilder hm = new StringBuilder();
				hm.Append("Encryption used: " + WZ.encryption.get_encryption_name());
				hm.Append("\r\n\r\n");
				foreach(wz_file f in WZ.wz_files){
					hm.Append(f.header.file_name);
					hm.Append(", Version: ");
					hm.Append(Convert.ToString(f.header.c_version, CultureInfo.InvariantCulture));
					hm.Append("\r\n");
					hm.Append(f.header.copyright.Substring(0, f.header.copyright.Length - 1));
					hm.Append("\r\n");
					hm.Append("Filesize: " + Convert.ToString(f.header.file_size) + " Bytes");
					hm.Append("\r\n");
					hm.Append("Datasize: " + Convert.ToString(f.header.data_size) + " Bytes");
					hm.Append("\r\n");
					hm.Append("Headersize: " + Convert.ToString(f.header.head_size) + " Bytes");
					hm.Append("\r\n\r\n");
				}
				hm.Remove(hm.Length - 4, 4);
				handle_controls(1);
				txtType.Text		= "WZ header information";
				textBox8.Text		= hm.ToString();
				textBox8.Visible	= true;
			}
			else {
				MessageBox.Show("Please open a file first!", "Header error", MessageBoxButtons.OK, MessageBoxIcon.Error, MessageBoxDefaultButton.Button1, 0);
			}
		}
		
		void ToolStripTextBox1KeyDown(object sender, KeyEventArgs e)
		{
			if(e.KeyCode == Keys.Enter){
				mnuExtras.HideDropDown();
				if(treeView1.Nodes.Count == 0)
				{
					MessageBox.Show("Open a file first!");
					return;
				}
				if(!SearchTree(treeView1.Nodes[0], toolStripTextBox1.Text))
				{
					MessageBox.Show("Not found!");
				}
			}
		}
		
		void PreferencesToolStripMenuItemClick(object sender, EventArgs e)
		{
			PrefForm pref = new PrefForm();
			pref.Show();
		}

		void MainForm_Load(object sender, EventArgs e)
		{			
			Load_XML_Preferences();
		}

		void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
		{
			treeView2.SelectedNode = resolve_UOL((UOL)treeView2.SelectedNode.Tag, treeView2.SelectedNode);
			treeView2.Focus();
		}

		void saveXMLFileToolStripMenuItem_Click(object sender, EventArgs e)
		{
			// Here we'll save to wzextract subdirectory XMLs infos about the WZ file
			string str_app = Application.StartupPath;

			// If Base.wz is opened, his img will be saved, the size of the files, and the files
			// for every wz file will be created
			XmlWriter XML;
			object t_img_d = null;

			bool proceed_analyzing = false;

			TreeNode[] tree_basis = new TreeNode[5];
			int[] tree_nb_entries = new int[5];
			int[] cpt_level = new int[5];
			int tree_level = 0;

			string filename;
			string type = "";
			image t_img;
			int number_to_check;
			bool xml_exists = false;
			DialogResult dlg_result;

			if (WZ.wz_files.Count > 0)
			{
				// We'll check if there are already WZ Files and we will ask for erasing
				if (WZ.has_basewz)
				{
					foreach (wz_file f in WZ.wz_files)
					{
						if (File.Exists(str_app + "\\Info_" + f.header.file_name + ".xml"))
						{
							xml_exists = true;
						}
					}

					if (xml_exists == true)
					{
						dlg_result = MessageBox.Show("There are one or more XML Files which already exist.\nThese XML files will be overwritten. Do you want to continue ?", "WzExtract - XML Files already existing", MessageBoxButtons.YesNo, MessageBoxIcon.Exclamation, MessageBoxDefaultButton.Button1);

						if (dlg_result == DialogResult.No)
						{
							return;
						}
					}
					
					XML = new XmlTextWriter(str_app + "\\Info_Base.wz.xml", Encoding.Default);
					tree_basis[0] = treeView1.Nodes[0];

					XML.WriteStartDocument();
					XML.WriteStartElement("WZ");

						XML.WriteStartElement("Number");
							XML.WriteValue(tree_basis[0].GetNodeCount(false));
						XML.WriteEndElement();

						for (int i = 0; i < tree_basis[0].GetNodeCount(false); i++)
						{
							t_img_d = tree_basis[0].Nodes[i].Tag;
							type = t_img_d.GetType().Name;

							if (type == "image")
							{
								t_img = (image)t_img_d;
								XML.WriteStartElement(t_img.name);
									XML.WriteStartElement("Type");
										XML.WriteString("IMG");
									XML.WriteEndElement();
									XML.WriteStartElement("Size");
										XML.WriteValue(t_img.size);
									XML.WriteEndElement();
									XML.WriteStartElement("Cs32");
										XML.WriteValue(t_img.cs32);
									XML.WriteEndElement();
								XML.WriteEndElement();
							}
							else
							{
								long filesize = 0;
								foreach (wz_file f in WZ.wz_files)
								{
									if (f.header.file_name == tree_basis[0].Nodes[i].Text + ".wz")
									{
										filesize = f.header.file_size;
									}
								}

								XML.WriteStartElement(tree_basis[0].Nodes[i].Text);
									XML.WriteStartElement("Type");
										XML.WriteString("WZ");
									XML.WriteEndElement();
									XML.WriteStartElement("Size");
										XML.WriteValue(filesize);
									XML.WriteEndElement();
								XML.WriteEndElement();
							}
						}

					XML.WriteEndElement();
					XML.WriteEndDocument();
					XML.Close();
					number_to_check = tree_basis[0].GetNodeCount(false);
				}
				else
				{
					foreach (wz_file f in WZ.wz_files)
					{
						if (File.Exists(str_app + "\\Info_" + f.header.file_name + ".xml"))
						{
							xml_exists = true;
						}
					}

					if (xml_exists == true)
					{
						dlg_result = MessageBox.Show("There is already one XML File for this wz file.\nThe XML file will be overwritten. Do you want to continue ?", "WzExtract - XML File already existing", MessageBoxButtons.YesNo, MessageBoxIcon.Exclamation, MessageBoxDefaultButton.Button1);

						if (dlg_result == DialogResult.No)
						{
							return;
						}
					}
					number_to_check = 1;
				}

				for (int i = 0; i < number_to_check; i++)
				{
					if (WZ.has_basewz)
					{
						tree_basis[0] = treeView1.Nodes[0].Nodes[i];
						filename = treeView1.Nodes[0].Nodes[i].Text;
						if (filename.Length > 3)
						{

							if (filename.Substring(filename.Length - 3, 3) != ".wz")
							{
								if (filename.Length > 4)
								{
									if (filename.Substring(filename.Length - 4, 4) == ".img")
									{
										proceed_analyzing = false;
									}
									else
									{
										proceed_analyzing = true;
										filename += ".wz";
									}
								}
								else
								{
									proceed_analyzing = true;
									filename += ".wz";
								}
							}
						}
						else
						{
							proceed_analyzing = true;
							filename += ".wz";
						}
					}
					else
					{
						tree_basis[0] = treeView1.Nodes[0];
						filename = treeView1.Nodes[0].Text;
						proceed_analyzing = true;
					}

					tree_level = 0; cpt_level[0] = 0;
					if (proceed_analyzing == true)
					{
						XML = new XmlTextWriter(str_app + "\\Info_" + filename + ".xml", Encoding.Default);

						XML.WriteStartDocument();
						XML.WriteStartElement("WZ");

							tree_nb_entries[0] = tree_basis[0].GetNodeCount(false);
							XML.WriteStartElement("Number");
								XML.WriteValue(tree_nb_entries[0]);
							XML.WriteEndElement();


							do
							{
								Application.DoEvents();

								t_img_d = tree_basis[tree_level].Nodes[cpt_level[tree_level]].Tag;
								type = t_img_d.GetType().Name;

								if (type == "image")
								{
									t_img = (image)t_img_d;
									XML.WriteStartElement("IMG_" + t_img.name);
										XML.WriteStartElement("Type");
											XML.WriteString("IMG");
										XML.WriteEndElement();
										XML.WriteStartElement("Size");
											XML.WriteValue(t_img.size);
										XML.WriteEndElement();
										XML.WriteStartElement("Cs32");
											XML.WriteValue(t_img.cs32);
										XML.WriteEndElement();
									XML.WriteEndElement();

								check_again:
									if (tree_level > 0 && cpt_level[tree_level] == tree_nb_entries[tree_level] - 1)
									{
										XML.WriteEndElement();
										tree_level -= 1;
										goto check_again;
									}
									else
									{
										cpt_level[tree_level] += 1;
									}
								}
								else
								{
									XML.WriteStartElement(tree_basis[tree_level].Nodes[cpt_level[tree_level]].Text);
										XML.WriteStartElement("Type");
											XML.WriteString("DIR");
										XML.WriteEndElement();

										tree_basis[tree_level + 1] = tree_basis[tree_level].Nodes[cpt_level[tree_level]];
										tree_nb_entries[tree_level + 1] = tree_basis[tree_level + 1].GetNodeCount(false);

										XML.WriteStartElement("Number");
											XML.WriteValue(tree_nb_entries[tree_level + 1]);
										XML.WriteEndElement();

										tree_level += 1;
										cpt_level[tree_level] = 0;
								}
							} while (cpt_level[0] < tree_nb_entries[0]);

						XML.WriteEndElement();
						XML.WriteEndDocument();
						XML.Close();
					}
				}

				MessageBox.Show("File Saving done successfully", "WzExtract - File Saving Successful", MessageBoxButtons.OK,MessageBoxIcon.Information);
			}
			else
			{
				MessageBox.Show("XML File Saving cannot be done if there is no file opened !", "XML Saving Error", MessageBoxButtons.OK, MessageBoxIcon.Exclamation, MessageBoxDefaultButton.Button1, 0);
			}
		}

		void compareToXMLFileToolStripMenuItem_Click(object sender, EventArgs e)
		{
			// Now the goal is to compare, we'll read the xml and check if the IMG are present and so on
			// If Base.wz is opened, all will be compared
			
			string str_app = Application.StartupPath;
			XmlReader XML;
			int[] tree_nb_entries = new int[5];
			TreeNode[] tree_basis = new TreeNode[5];
			string analyzed_entry = "";
			int analyzed_size = 0;
			int analyzed_checksum = 0;
			TreeNode analyzed_node;
			object t_img_d = null;
			image t_img;
			int number_to_check = 0;
			int[] cpt_level = new int[5];
			bool[] changed_level = new bool[5];
			int tree_level = 0;


			int run_time = Environment.TickCount;

			treeView1.BeginUpdate();


			if (WZ.wz_files.Count > 0)
			{
 
				if (WZ.has_basewz)
				{
					// First we check that the Base.wz exists
					if (!File.Exists(str_app + "\\Info_Base.wz.xml"))
					{
						treeView1.EndUpdate();
						MessageBox.Show("There is no XML File about Base.wz, so the Comparison cannot be done.\nYou have first to save XMLs with Base.wz with another version opened.","WzExtract - Unable to compare Base.wz",MessageBoxButtons.OK,MessageBoxIcon.Exclamation);
						return;
					}

					// We check that the file analyzed exists in XML
					// If it's a single file opened, impossible to continue
					// If Base.wz is opened, we check if all files exists
					// If not, send a warning asking if we continue or not
					bool xml_missing = false;

					foreach (wz_file f in WZ.wz_files)
					{
						if (!File.Exists(str_app + "\\Info_" + f.header.file_name + ".xml"))
						{
							xml_missing = true;
						}
					}

					if (xml_missing == true)
					{
						DialogResult dlg_result;
						treeView1.EndUpdate();
						dlg_result = MessageBox.Show("There is one or more XML File missing to compare all the files with Base.wz.\nComparison will consider missing file as entirely new entries. Do you still want to do the Comparison ?", "WzExtract - XML Files missing for Comparison", MessageBoxButtons.YesNo, MessageBoxIcon.Exclamation, MessageBoxDefaultButton.Button2);

						if (dlg_result == DialogResult.No)
						{
							return;
						}
						treeView1.BeginUpdate();
					}

					// Base.wz will be analyzed first, to find the changes
					XML = XmlReader.Create(str_app + "\\Info_Base.wz.xml");
					XML.Read();
					XML.ReadStartElement("WZ");
					XML.ReadStartElement("Number");
					tree_nb_entries[0] = XML.ReadContentAsInt();
					XML.ReadEndElement();

					for (int i = 0; i < tree_nb_entries[0]; i++)
					{
						analyzed_entry = XML.Name;
						XML.ReadStartElement();
						XML.ReadStartElement("Type");

						switch (XML.ReadContentAsString())
						{
							case "WZ":
								XML.ReadEndElement();
								XML.ReadStartElement("Size");
								analyzed_size = XML.ReadContentAsInt();
								XML.ReadEndElement();
								XML.ReadEndElement();

								// Now let's compare the size of the current file
								foreach (wz_file f in WZ.wz_files)
								{
									if (f.header.file_name == analyzed_entry + ".wz")
									{
										if (f.header.file_size != analyzed_size)
										{
											// The file size changed let's color it
											analyzed_node = FindNode(treeView1.Nodes[0], analyzed_entry);
											analyzed_node.BackColor = System.Drawing.Color.Yellow;
										}
										else
										{
											analyzed_node = FindNode(treeView1.Nodes[0], analyzed_entry);
											analyzed_node.BackColor = System.Drawing.Color.LightGray;
										}
									}
								}

								break;
							case "IMG":
								XML.ReadEndElement();
								XML.ReadStartElement("Size");
								analyzed_size = XML.ReadContentAsInt();
								XML.ReadEndElement();
								XML.ReadStartElement("Cs32");
								analyzed_checksum = XML.ReadContentAsInt();
								XML.ReadEndElement();
								XML.ReadEndElement();

								// Now let's compare the size and checksum of the current img
								analyzed_node = FindNode(treeView1.Nodes[0], analyzed_entry);
								t_img_d = analyzed_node.Tag;
								t_img = (image)t_img_d;

								if (t_img.size != analyzed_size || t_img.cs32 != analyzed_checksum)
								{
									analyzed_node.BackColor = System.Drawing.Color.Yellow;
								}
								else
								{
									analyzed_node.BackColor = System.Drawing.Color.LightGray;
								}
								break;
						}
						number_to_check += 1;
					}

					XML.Close();
				}
				else
				{
					foreach (wz_file f in WZ.wz_files)
					{
						if (!File.Exists(str_app + "\\Info_" + f.header.file_name + ".xml"))
						{
							treeView1.EndUpdate();
							MessageBox.Show("There is no XML File about " + f.header.file_name + ", so the Comparison cannot be done. You have first to save a XML with " + f.header.file_name + " with another version opened.", "WzExtract - Unable to compare " + f.header.file_name, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
							return;
						}
					}
					
					number_to_check = 1;
				}


				// Now we check every img located in each wz file (or the only one loaded)
				foreach (wz_file f in WZ.wz_files)
				{
					if (WZ.has_basewz)
					{
						for (int i = 0; i < treeView1.Nodes[0].GetNodeCount(false); i++)
						{
							if (treeView1.Nodes[0].Nodes[i].Text + ".wz" == f.header.file_name)
							{
								tree_basis[0] = treeView1.Nodes[0].Nodes[i];
							}
						}
					}
					else
					{

						tree_basis[0] = treeView1.Nodes[0];
					}

					if (f.header.file_name != "Base.wz")
					{
						// We have to ignore the file where the XML is missing
						if (File.Exists(str_app + "\\Info_" + f.header.file_name + ".xml"))
						{

							tree_level = 0;
							cpt_level[0] = 0;

							XML = XmlReader.Create(str_app + "\\Info_" + f.header.file_name + ".xml");
							XML.Read();
							XML.ReadStartElement("WZ");
							XML.ReadStartElement("Number");
							tree_nb_entries[0] = XML.ReadContentAsInt();
							XML.ReadEndElement();

							do
							{
								Application.DoEvents();
								analyzed_entry = XML.Name;
								XML.ReadStartElement();
								XML.ReadStartElement("Type");

								switch (XML.ReadContentAsString())
								{
									case "DIR":
										// We have a directory so we increase the level analyzed
										XML.ReadEndElement();
										XML.ReadStartElement("Number");
										tree_nb_entries[tree_level + 1] = XML.ReadContentAsInt();
										XML.ReadEndElement();

										changed_level[tree_level + 1] = false;
										cpt_level[tree_level + 1] = 0;
										tree_basis[tree_level + 1] = FindNode(tree_basis[tree_level], analyzed_entry);
										tree_level += 1;

										break;
									case "IMG":
										// We compare the data about the IMG with the one in the tree
										analyzed_entry = analyzed_entry.Substring(4, analyzed_entry.Length - 4);
										XML.ReadEndElement();
										XML.ReadStartElement("Size");
										analyzed_size = XML.ReadContentAsInt();
										XML.ReadEndElement();
										XML.ReadStartElement("Cs32");
										analyzed_checksum = XML.ReadContentAsInt();
										XML.ReadEndElement();
										XML.ReadEndElement();

										// Now let's compare the size and checksum of the current img
										analyzed_node = FindNode(tree_basis[tree_level], analyzed_entry);

										if (analyzed_node != null)
										{
											// If it's null it's mean the entry has been deleted
											t_img_d = analyzed_node.Tag;
											t_img = (image)t_img_d;

											if (t_img.size != analyzed_size || t_img.cs32 != analyzed_checksum)
											{
												analyzed_node.BackColor = System.Drawing.Color.Yellow;
												changed_level[tree_level] = true;
											}
											else
											{

												analyzed_node.BackColor = System.Drawing.Color.LightGray;
											}
										}


									check_again:
										if (tree_level > 0 && cpt_level[tree_level] == tree_nb_entries[tree_level] - 1)
										{
											XML.ReadEndElement();

											// We color the directory if he has changed or not
											if (changed_level[tree_level] == true)
											{
												tree_basis[tree_level].BackColor = System.Drawing.Color.Yellow;
											}
											else
											{
												tree_basis[tree_level].BackColor = System.Drawing.Color.LightGray;
											}

											tree_level -= 1;
											goto check_again;
										}
										else
										{
											cpt_level[tree_level] += 1;
										}

									break;
								}
							} while (cpt_level[0] < tree_nb_entries[0]);

							XML.Close();
						}
					}
				}

				treeView1.EndUpdate(); 
				MessageBox.Show("File Comparison done in " + (Environment.TickCount - run_time).ToString() + " ms\n\nGrey : Entries with no changes\nYellow : Entries which have been modified\nWhite : New Entries","WzExtract - File Comparison Successful",MessageBoxButtons.OK,MessageBoxIcon.Information);
			}
			else
			{
				treeView1.EndUpdate();
				MessageBox.Show("File Comparison cannot be done if there is no file opened !", "WzExtract - Unable to compare no files", MessageBoxButtons.OK, MessageBoxIcon.Exclamation, MessageBoxDefaultButton.Button1, 0);
			}
		}

		void chkCloseRender_Click(object sender, EventArgs e)
		{
			renderContainer.Visible = false;
			mnuFile.Visible			= true;
			mnuExtras.Visible		= true;
			mnuAbout.Visible		= true;
			mnuCloseRender.Visible	= false;
		}

		void closeRenderToolStripMenuItem_Click(object sender, EventArgs e)
		{
			renderContainer.Visible	= false;
			mnuCloseRender.Visible	= false;
			mnuFile.Visible			= true;
			mnuExtras.Visible		= true;
			mnuAbout.Visible		= true;
		}
		
		void AboutToolStripMenuItemClick(object sender, EventArgs e)
		{
			AboutForm about = new AboutForm();
			about.Show();
		}
		
		void LicenseToolStripMenuItemClick(object sender, EventArgs e)
		{
			License lic = new License();
			lic.Show();
		}
		
		void CmdRedrawRenderClick(object sender, EventArgs e)
		{
			button2.PerformClick();
		}
		
		void CmdCloseRenderClick(object sender, EventArgs e)
		{
			mnuCloseRender.PerformClick();
		}
		
		void CmdSaveRenderClick(object sender, EventArgs e)
		{
			string map_name = treeView1.SelectedNode.Text;
			map_name = map_name.Substring(0, map_name.Length - 4);
			
			SaveFileDialog dlgSave = new SaveFileDialog();
			dlgSave.Title = "Save Map Rendered";
			dlgSave.Filter = "PNG image|*.png|GIF image|*.gif|BMP image|*.bmp|JPG image|*.jpg";
			dlgSave.FileName = map_name;
			if (pref.render_path != "") { dlgSave.InitialDirectory = pref.render_path; }
			if (dlgSave.ShowDialog() == DialogResult.OK)
			{
				
				switch (dlgSave.FilterIndex)
				{
					case 1:
						picRender.Image.Save(dlgSave.FileName, ImageFormat.Png);
						break;
					case 2:
						picRender.Image.Save(dlgSave.FileName, ImageFormat.Gif);
						break;
					case 3:
						picRender.Image.Save(dlgSave.FileName, ImageFormat.Bmp);
						break;
					case 4:
						picRender.Image.Save(dlgSave.FileName, ImageFormat.Jpeg);
						break;
					default:
						picRender.Image.Save(dlgSave.FileName, ImageFormat.Png);
						break;
				}
			}
			dlgSave.Dispose();
		}
		
		void ChkPortalCheckedChanged(object sender, EventArgs e)
		{
			chkPortalr.Checked = chkPortal.Checked;
		}
		
		void ChkPortalrCheckedChanged(object sender, EventArgs e)
		{
			chkPortal.Checked = chkPortalr.Checked;
		}
		
		void ChkReactorCheckedChanged(object sender, EventArgs e)
		{
			chkReactorr.Checked = chkReactor.Checked;
		}
		
		void ChkReactorrCheckedChanged(object sender, EventArgs e)
		{
			chkReactor.Checked = chkReactorr.Checked;
		}
		
		void ChkMobCheckedChanged(object sender, EventArgs e)
		{
			chkMobr.Checked = chkMob.Checked;
		}
		
		void ChkMobrCheckedChanged(object sender, EventArgs e)
		{
			chkMob.Checked = chkMobr.Checked;
		}
		
		void ChkNPCCheckedChanged(object sender, EventArgs e)
		{
			chkNPCr.Checked = chkNPC.Checked;
		}
		
		void ChkNPCrCheckedChanged(object sender, EventArgs e)
		{
			chkNPC.Checked = chkNPCr.Checked;
		}
		
		void Button1Click(object sender, EventArgs e)
		{
			image img = (image)treeView1.SelectedNode.Tag;
			FileStream	save	= new FileStream(img.name, FileMode.Create);
			byte[]		buffer	= new byte[img.size];
			(WZ.wz_files[img.wz_f]).stream.Position	= img.offs;
			(WZ.wz_files[img.wz_f]).stream.Read(buffer, 0, img.size);
			save.Write(buffer, 0, buffer.Length);
			save.Close();
		}
		
		void Button3Click(object sender, EventArgs e)
		{
			if(WZ.mp3_stream == null || WZ.mp3_stream.Disposed) {
				MP3		mp3				= (MP3)treeView2.SelectedNode.Tag;
						WZ.audio_path		= Path.GetTempPath() + '\\' + treeView2.SelectedNode.Text + ".mp3";
				saveMP3((MP3)treeView2.SelectedNode.Tag, WZ.audio_path, WZ.wz_files[((image)treeView1.SelectedNode.Tag).wz_f]);
				WZ.mp3_stream				= new Audio(WZ.audio_path);
				trackBar1.Maximum		= (int)WZ.mp3_stream.Duration;
	
			}
			button3.Enabled		= false;
			button4.Enabled		= true;
			button5.Enabled		= true;
			WZ.mp3_stream.Play();
			timer1.Start();
		}
		
		void Button4Click(object sender, EventArgs e)
		{
			if(WZ.mp3_stream.Paused){
				WZ.mp3_stream.Play();
				timer1.Start();
				button4.Text = "Pause";
			} else {
				WZ.mp3_stream.Pause();
				timer1.Stop();
				button4.Text = "Resume";
			}
		}
		
		void Button5Click(object sender, EventArgs e)
		{
			if(WZ.mp3_stream != null && (WZ.mp3_stream.Playing || WZ.mp3_stream.Paused)){
				WZ.mp3_stream.Stop();
				timer1.Stop();
				button3.Enabled		= true;
				button4.Enabled		= false;
				button5.Enabled		= false;
				button4.Text		= "Pause";
				trackBar1.Value		= 0;
				label4.Text			= "00:00 /";
			}
		}
		
		void Timer1Tick(object sender, EventArgs e)
		{
			if(WZ.mp3_stream.CurrentPosition == WZ.mp3_stream.Duration) {
				if(checkBox1.Checked){
					WZ.mp3_stream.CurrentPosition = 0;
				} else {
					WZ.mp3_stream.Stop();
					button3.Enabled = true;
					button4.Enabled = false;
					trackBar1.Value = 0;
				}
			}
			trackBar1.Value		= (int)WZ.mp3_stream.CurrentPosition;
			TimeSpan time		= TimeSpan.FromSeconds(WZ.mp3_stream.CurrentPosition);
			label4.Text			= Convert.ToString(time.Minutes).PadLeft(2, '0') + ":" + Convert.ToString(time.Seconds).PadLeft(2, '0') + " /";
		}
		
		void TrackBar1Scroll(object sender, EventArgs e)
		{
			if(WZ.mp3_stream != null) {
				WZ.mp3_stream.CurrentPosition = trackBar1.Value;
			}
		}
		
		void MnuExtractClick(object sender, System.EventArgs e)
		{
			extractCount.Text		= "";
			extractBar.Maximum		= WZ.img_number;
			extractBar.Value		= 0;
			fullExtractPanel.Dock	= DockStyle.Fill;
			extractStart.Enabled	= true;
			fullExtractPanel.Show();
		}
		
		void ExtractStartClick(object sender, EventArgs e)
		{
			handle_controls(1);	
			menuStrip1.Enabled		= false;
			extractStart.Enabled	= false;
			is_extr					= true;			
			int count				= 0;	
			int extract_StartTime	= Environment.TickCount;
			full_extract(treeView1.Nodes[0], Application.StartupPath + "\\extract\\" + treeView1.Nodes[0].Text + "\\", ref count);
			toolStripStatusLabel1.Text = "Full extract completed. Needed " + Convert.ToString(Environment.TickCount - extract_StartTime) + " ms.";
			extractCancel.PerformClick();
		}
		
		void ExtractCancelClick(object sender, EventArgs e)
		{
			is_extr = false;
			fullExtractPanel.Hide();
			menuStrip1.Enabled		= true;
			extractStart.Enabled	= true;
		}
		
		void Button6Click(object sender, EventArgs e)
		{
			image img = (image)treeView1.SelectedNode.Tag;
			full_extract_img(img, img.node, Application.StartupPath + "\\extract\\" + img.name + "\\");
			MessageBox.Show("image extracted");
		}

        //exprot map xml
        private void button7_Click(object sender, EventArgs e)
        {
            MapTreevieToXML(treeView2);
        }

        private TreeView thetreeview;
        private string xmlfilepath;
        private XmlTextWriter textWriter;
        private XmlNode Xmlroot;
        private XmlDocument textdoc =  new XmlDocument();
        private int MapTreevieToXML(TreeView TheTreeView)
        {
            string file = TheTreeView.TopNode.Text;
            string[] name = file.Split(new char[] {'.'});
            string end_name = string.Format("map name = \"{0}\"", name[0]);
            String XMLFilePath = String.Format(".\\extract\\{0}.xml", name[0]);

            //-------初始化转换环境变量
            thetreeview = TheTreeView;
            xmlfilepath = XMLFilePath;
            textWriter = new XmlTextWriter(xmlfilepath, null);

            //-------创建XML写操作对象
            textWriter.Formatting = Formatting.Indented;

            //-------开始写过程，调用WriteStartDocument方法
            textWriter.WriteStartDocument();

            //-------写入说明
            //textWriter.WriteComment("this　XML　is　created　from　a　tree");
            //textWriter.WriteComment("By　思月行云");

            //-------添加第一个根节点
            textWriter.WriteStartElement(end_name);
            textWriter.WriteEndElement();

            //------　写文档结束，调用WriteEndDocument方法
            textWriter.WriteEndDocument();

            //-----关闭输入流
            textWriter.Close();

            //-------创建XMLDocument对象
            textdoc.Load(xmlfilepath);          
            

            //------选中根节点
            XmlElement Xmlnode = textdoc.CreateElement(thetreeview.Nodes[0].Text);
            Xmlroot = textdoc.SelectSingleNode("map");

            //------遍历原treeview控件，并生成相应的XML
            TransMapTree(thetreeview.Nodes[0].Nodes, (XmlElement)Xmlroot,"map");

            return 0;
        }

        private int TransTreeSav(TreeNodeCollection nodes, XmlElement ParXmlnode)
        {

            //-------遍历树的各个故障节点，同时添加节点至XML
            XmlElement xmlnode;
            Xmlroot = textdoc.SelectSingleNode("TreeExXMLCls");

            foreach (TreeNode node in nodes)
            {
                xmlnode = textdoc.CreateElement(node.Text);
                ParXmlnode.AppendChild(xmlnode);

                if (node.Nodes.Count > 0)
                {
                    TransTreeSav(node.Nodes, xmlnode);
                }
            }
            textdoc.Save(xmlfilepath);

            return 0;
        }
        
        private int TransMapBase(TreeNodeCollection nodes, XmlElement ParXmlnode){
            int index = 0;
            foreach (TreeNode node in nodes)
            {
                XmlElement xmlnode = textdoc.CreateElement("i");
                ParXmlnode.AppendChild(xmlnode);
                xmlnode.SetAttribute("name", index.ToString());                
                foreach (TreeNode node1 in node.Nodes)
                {   
                    xmlnode.SetAttribute(node1.Text,node1.Tag.ToString());
                }
                index++;
            }
            return 0;
        }

        private int TransMapLayer(TreeNodeCollection nodes, XmlElement ParXmlnode)
        {
            //info
            if(null != nodes[0].Tag)
                ParXmlnode.SetAttribute(nodes[0].Text, nodes[0].Tag.ToString());

            //tile
            XmlElement tileXmlNode = textdoc.CreateElement("tile");
            ParXmlnode.AppendChild(tileXmlNode);
            tileXmlNode.SetAttribute("name", nodes[1].Text);
            int tile_index1 = 0;
            foreach (TreeNode tile_node in nodes[1].Nodes)
            {
                XmlElement node = textdoc.CreateElement("t");
                tileXmlNode.AppendChild(node);
                node.SetAttribute("name",tile_index1.ToString());                
                foreach (TreeNode node1 in tile_node.Nodes)
                {              
                    node.SetAttribute(node1.Text, node1.Tag.ToString());                
                }
                tile_index1++;
            }

            //obj
            XmlElement objXmlNode = textdoc.CreateElement("obj");
            ParXmlnode.AppendChild(objXmlNode);
            objXmlNode.SetAttribute("name", nodes[2].Text);
            int obj_index1 = 0;
            foreach (TreeNode obj_node in nodes[2].Nodes)
            {
                XmlElement node = textdoc.CreateElement("o");
                objXmlNode.AppendChild(node);
                node.SetAttribute("name",obj_index1.ToString());                
                foreach (TreeNode node1 in obj_node.Nodes)
                {   
                    node.SetAttribute(node1.Text, node1.Tag.ToString());
                }
                obj_index1++;
            }

            return 0;
        }
        private int TransMapFoothold(TreeNodeCollection nodes, XmlElement ParXmlnode)
        {
            foreach (TreeNode node in nodes)
            {
                XmlElement element1 = textdoc.CreateElement("i");
                ParXmlnode.AppendChild(element1);
                element1.SetAttribute("name", node.Text);
                foreach (TreeNode node1 in node.Nodes)
                {
                    XmlElement element2 = textdoc.CreateElement("i");
                    element1.AppendChild(element2);
                    element2.SetAttribute("name", node1.Text);
                    foreach (TreeNode node2 in node1.Nodes)
                    {
                        XmlElement element3 = textdoc.CreateElement("i");
                        element2.AppendChild(element3);
                        element3.SetAttribute("name", node2.Text);
                        foreach (TreeNode node3 in node2.Nodes)
                        {
                            element3.SetAttribute(node3.Text, node3.Tag.ToString());
                        }
                    }
                }
            }
            return 0;
        }
        private int TransMapPortal(TreeNodeCollection nodes, XmlElement ParXmlnode)
        {
            int index = 0;
            foreach (TreeNode node in nodes)
            {
                XmlElement element1 = textdoc.CreateElement("p");
                ParXmlnode.AppendChild(element1);
                element1.SetAttribute("name", index.ToString());
                foreach (TreeNode node1 in node.Nodes)
                {     
                    element1.SetAttribute(node1.Text, node1.Tag.ToString());
                }
                index++;
            }
            return 0;
        }

        private int TransMapLadderRope(TreeNodeCollection nodes, XmlElement ParXmlnode)
        {
            int index = 0;
            foreach (TreeNode node in nodes)
            {
                XmlElement element1 = textdoc.CreateElement("l");
                ParXmlnode.AppendChild(element1);
                element1.SetAttribute("name", index.ToString());
                foreach (TreeNode node1 in node.Nodes)
                {
                    element1.SetAttribute(node1.Text, node1.Tag.ToString());
                }
                index++;
            }
            return 0;
        }

        private int TransMap1(TreeNodeCollection nodes, XmlElement ParXmlnode)
        {
            foreach (TreeNode node in nodes)
            {
                ParXmlnode.SetAttribute(node.Text, node.Tag.ToString());                
            }
            return 0;
        }

        private int TransMapTree(TreeNodeCollection nodes, XmlElement ParXmlnode,String name)
        {
            XmlElement xmlnode;
            //-------遍历树的各个故障节点，同时添加节点至XML            
            Xmlroot = textdoc.SelectSingleNode(name);            
            foreach (TreeNode node in nodes)
            {        
               if("info".Equals(node.Text))
                {
                    xmlnode = textdoc.CreateElement("info");
                    ParXmlnode.AppendChild(xmlnode);
                    xmlnode.SetAttribute("name", node.Text);
                    foreach(TreeNode node1 in node.Nodes)
                        xmlnode.SetAttribute(node1.Text, node1.Tag.ToString());
                    continue;
                }
                else if ("back".Equals(node.Text)){
                    xmlnode = textdoc.CreateElement(node.Text);
                    ParXmlnode.AppendChild(xmlnode);
                    xmlnode.SetAttribute("name", node.Text);
                    TransMapBase(node.Nodes, xmlnode);
                    continue;
                }
                else if ("life".Equals(node.Text))
                {
                    xmlnode = textdoc.CreateElement(node.Text);
                    ParXmlnode.AppendChild(xmlnode);
                    xmlnode.SetAttribute("name", node.Text);
                    TransMapBase(node.Nodes, xmlnode);
                    continue;
                }
                else if ("reactor".Equals(node.Text))
                {
                    xmlnode = textdoc.CreateElement(node.Text);
                    ParXmlnode.AppendChild(xmlnode);
                    xmlnode.SetAttribute("name", node.Text);
                    TransMapBase(node.Nodes, xmlnode);
                    continue;
                }                
                else if ("0".Equals(node.Text) || "1".Equals(node.Text) || "2".Equals(node.Text) || "3".Equals(node.Text) || "4".Equals(node.Text) || "5".Equals(node.Text) || "6".Equals(node.Text) || "7".Equals(node.Text))
                {
                    xmlnode = textdoc.CreateElement("layer");
                    ParXmlnode.AppendChild(xmlnode);
                    xmlnode.SetAttribute("name", node.Text);
                    TransMapLayer(node.Nodes, xmlnode);
                    continue;
                }                
                else if ("foothold".Equals(node.Text))
                {
                    xmlnode = textdoc.CreateElement(node.Text);
                    ParXmlnode.AppendChild(xmlnode);
                    xmlnode.SetAttribute("name", node.Text);
                    TransMapFoothold(node.Nodes, xmlnode);
                    continue;
                }
                else if ("ladderRope".Equals(node.Text))
                {
                    xmlnode = textdoc.CreateElement(node.Text);
                    ParXmlnode.AppendChild(xmlnode);
                    xmlnode.SetAttribute("name", node.Text);
                    TransMapLadderRope(node.Nodes, xmlnode);
                    continue;
                }
                else if ("miniMap".Equals(node.Text))
                {
                    xmlnode = textdoc.CreateElement(node.Text);
                    ParXmlnode.AppendChild(xmlnode);
                    xmlnode.SetAttribute("name", node.Text);
                    TransMap1(node.Nodes, xmlnode);
                    continue;                    
                }
                else if ("portal".Equals(node.Text))
                {
                    xmlnode = textdoc.CreateElement("p");
                    ParXmlnode.AppendChild(xmlnode);
                    xmlnode.SetAttribute("name", node.Text);
                    TransMapPortal(node.Nodes, xmlnode);
                    continue;
                }
               continue;
            }
            textdoc.Save(xmlfilepath);

            return 0;
        }

        //export obj xml
        private void button8_Click(object sender, EventArgs e)
        {
            ObjTreevieToXML (treeView2);
        }

        private int ObjTreevieToXML(TreeView TheTreeView)
        {
            string file = TheTreeView.TopNode.Text;
            string[] name = file.Split(new char[] { '.' });
            string end_name = string.Format("map name = \"{0}\"", name[0]);
            String XMLFilePath = String.Format(".\\extract\\Map\\Obj\\{0}.xml", name[0]);

            //-------初始化转换环境变量
            thetreeview = TheTreeView;
            xmlfilepath = XMLFilePath;
            textWriter = new XmlTextWriter(xmlfilepath, null);

            //-------创建XML写操作对象
            textWriter.Formatting = Formatting.Indented;

            //-------开始写过程，调用WriteStartDocument方法
            textWriter.WriteStartDocument();

            //-------写入说明
            //textWriter.WriteComment("this　XML　is　created　from　a　tree");
            //textWriter.WriteComment("By　思月行云");

            //-------添加第一个根节点
            textWriter.WriteStartElement(end_name);
            textWriter.WriteEndElement();

            //------　写文档结束，调用WriteEndDocument方法
            textWriter.WriteEndDocument();

            //-----关闭输入流
            textWriter.Close();

            //-------创建XMLDocument对象
            textdoc.Load(xmlfilepath);


            //------选中根节点
            XmlElement Xmlnode = textdoc.CreateElement(thetreeview.Nodes[0].Text);
            Xmlroot = textdoc.SelectSingleNode("map");

            //------遍历原treeview控件，并生成相应的XML
            TransTileTree(thetreeview.Nodes[0].Nodes, (XmlElement)Xmlroot);

            return 0;
        }

        private String l1, l2, l3, l4;
        private int TransTileTree(TreeNodeCollection nodes, XmlElement xmlroot)
        {            
            foreach (TreeNode node1 in nodes)
            {
                l1 = node1.Text;
                foreach (TreeNode node2 in node1.Nodes)
                {
                    l2 = node2.Text;

                    XmlElement xmlnode1 = textdoc.CreateElement("i");
                    
                    foreach (TreeNode node3 in node2.Nodes)
                    {                        
                        if ("origin".Equals(node3.Text))
                        {
                            xmlroot.AppendChild(xmlnode1);

                            vector v = node3.Tag as vector;
                            xmlnode1.SetAttribute("origin_x", v.x.ToString());
                            xmlnode1.SetAttribute("origin_y", v.y.ToString());
                            xmlnode1.SetAttribute("img", string.Format("{0}.{1}.png", l1, l2));
                        }
                        else if ("z".Equals(node3.Text))
                        {
                            xmlnode1.SetAttribute("origin_z", node3.Tag.ToString());
                        }
                        else if ("delay".Equals(node3.Text))
                        {
                            xmlnode1.SetAttribute("delay", node3.Tag.ToString());
                        }
                        else if ("foothold".Equals(node3.Text))
                        {
                            if (node3.Tag == null)
                            {
                            }
                            else
                            {
                                xmlnode1.SetAttribute("foothold_x", (node3.Tag as vector).x.ToString());
                                xmlnode1.SetAttribute("foothold_y", (node3.Tag as vector).y.ToString());
                            }  
                        }
                        else
                        {
                            l3 = node3.Text;
                            XmlElement xmlnode2 = textdoc.CreateElement("i");
                            
                            foreach (TreeNode node4 in node3.Nodes)
                            {                                
                                if ("origin".Equals(node4.Text))
                                {
                                    xmlroot.AppendChild(xmlnode2);

                                    vector v = node4.Tag as vector;
                                    xmlnode2.SetAttribute("origin_x", v.x.ToString());
                                    xmlnode2.SetAttribute("origin_y", v.y.ToString());
                                    xmlnode2.SetAttribute("img", string.Format("{0}.{1}.{2}.png", l1, l2, l3));
                                }
                                else if ("z".Equals(node4.Text))
                                {
                                    xmlnode2.SetAttribute("origin_z", node4.Tag.ToString());
                                }
                                else if ("delay".Equals(node4.Text))
                                {
                                    xmlnode2.SetAttribute("delay", node4.Tag.ToString());
                                }
                                else if ("foothold".Equals(node4.Text))
                                {
                                    if (node4.Tag == null)
                                    {
                                    }
                                    else
                                    {
                                        xmlnode2.SetAttribute("foothold_x", (node4.Tag as vector).x.ToString());
                                        xmlnode2.SetAttribute("foothold_y", (node4.Tag as vector).y.ToString());
                                    }  
                                }
                                else
                                {
                                    l4 = node4.Text;

                                    XmlElement xmlnode3 = textdoc.CreateElement("i");                                    
                                    foreach (TreeNode node5 in node4.Nodes)
                                    {                                        
                                        if ("origin".Equals(node5.Text))
                                        {
                                            xmlroot.AppendChild(xmlnode3);
                                            vector v = node5.Tag as vector;
                                            xmlnode3.SetAttribute("origin_x", v.x.ToString());
                                            xmlnode3.SetAttribute("origin_y", v.y.ToString());
                                            xmlnode3.SetAttribute("img", string.Format("{0}.{1}.{2}.{3}.png", l1, l2, l3, l4));
                                        }
                                        else if ("z".Equals(node5.Text))
                                        {
                                            xmlnode3.SetAttribute("origin_z", node5.Tag.ToString());
                                        }
                                        else if ("delay".Equals(node5.Text))
                                        {
                                            xmlnode3.SetAttribute("delay", node5.Tag.ToString());
                                        }
                                        else if ("foothold".Equals(node5.Text))
                                        {
                                            if (node5.Tag == null)
                                            {
                                            }
                                            else
                                            {
                                                xmlnode3.SetAttribute("foothold_x", (node5.Tag as vector).x.ToString());
                                                xmlnode3.SetAttribute("foothold_y", (node5.Tag as vector).y.ToString());
                                            }
                                        }
                                    }                                   

                                }
                            }

                        }
                    }
                }                
            }
            textdoc.Save(xmlfilepath);
             
            return 0;
        }

	}
}