using System;
using System.Drawing;
using System.Windows.Forms;
using System.Xml;
using System.Text;

namespace WZextract
{
	public partial class PrefForm : Form
	{
		public PrefForm()
		{
			InitializeComponent();
		}
		
		void DirSelect(TextBox tb)
        {
			FolderBrowserDialog selectDir	= new FolderBrowserDialog();
			selectDir.Description			= "Please select the directory.";
			selectDir.ShowNewFolderButton	= true;
			
			if(selectDir.ShowDialog() == DialogResult.OK)
            {
				tb.Text = selectDir.SelectedPath;
			}
		}
		
		void Button2Click(object sender, EventArgs e)
		{
			this.Close();
		}
		
		void Button3Click(object sender, EventArgs e)
		{
			DirSelect(txtWZPath);
		}
		
		void Button4Click(object sender, EventArgs e)
		{
			DirSelect(txtPNGPath);
		}
		
		void Button5Click(object sender, EventArgs e)
		{
			DirSelect(txtMapPath);
		}

        void button6_Click(object sender, EventArgs e)
        {
            DirSelect(txtMP3Path);
        }
		
		void Button1Click(object sender, EventArgs e)
		{
            string str_app = Application.StartupPath;
			XmlWriter XML = new XmlTextWriter(str_app + "\\WZextract_settings.xml", Encoding.Default);
                XML.WriteStartDocument();
                    XML.WriteStartElement("Settings");
                        XML.WriteStartElement("WZ_Files");
                            if (txtWZPath.Text != "") { XML.WriteString(txtWZPath.Text); } else { XML.WriteString("None"); }
                        XML.WriteEndElement();
                        XML.WriteStartElement("PNGs");
                            if (txtPNGPath.Text != "") { XML.WriteString(txtPNGPath.Text); } else { XML.WriteString("None"); }
                        XML.WriteEndElement();
                        XML.WriteStartElement("Map_Renders");
                            if (txtMapPath.Text != "") { XML.WriteString(txtMapPath.Text); } else { XML.WriteString("None"); }
                        XML.WriteEndElement();
                        XML.WriteStartElement("MP3s");
                            if (txtMP3Path.Text != "") { XML.WriteString(txtMP3Path.Text); } else { XML.WriteString("None"); }
                        XML.WriteEndElement();
                        XML.WriteStartElement("Resolve_UOLs");
                            XML.WriteValue(chkResolveUOL.Checked);
                        XML.WriteEndElement();
                        XML.WriteStartElement("Language");
                            XML.WriteValue(cmbLanguage.SelectedIndex);
                        XML.WriteEndElement();

                    XML.WriteEndElement();
                XML.WriteEndDocument();
            XML.Close();

			this.Close();
		}

        private void PrefForm_Load(object sender, EventArgs e)
        {
            // Loading settings
            string str_xml = Application.StartupPath + "\\WZextract_settings.xml";



            if (System.IO.File.Exists(str_xml) == true)
            {
                XmlReader XML = XmlReader.Create(str_xml);

                XML.Read();
                XML.ReadStartElement("Settings");
                XML.ReadStartElement("WZ_Files"); txtWZPath.Text = XML.ReadString(); XML.ReadEndElement();
                XML.ReadStartElement("PNGs"); txtPNGPath.Text = XML.ReadString(); XML.ReadEndElement();
                XML.ReadStartElement("Map_Renders"); txtMapPath.Text = XML.ReadString(); XML.ReadEndElement();
                XML.ReadStartElement("MP3s"); txtMP3Path.Text = XML.ReadString(); XML.ReadEndElement();
                XML.ReadStartElement("Resolve_UOLs"); chkResolveUOL.Checked = XML.ReadContentAsBoolean(); XML.ReadEndElement();
                XML.ReadStartElement("Language"); cmbLanguage.SelectedIndex = XML.ReadContentAsInt(); XML.ReadEndElement();
                XML.Close();

                if (txtWZPath.Text == "None") { txtWZPath.Text = ""; }
                if (txtPNGPath.Text == "None") { txtPNGPath.Text = ""; }
                if (txtMapPath.Text == "None") { txtMapPath.Text = ""; }
                if (txtMP3Path.Text == "None") { txtMP3Path.Text = ""; }
            }
            else
            {
                // File not existing so we create a new one with default options
                XmlWriter XML = new XmlTextWriter(str_xml, Encoding.Default);
                XML.WriteStartDocument();
                    XML.WriteStartElement("Settings");
                        XML.WriteStartElement("WZ_Files");
                            XML.WriteString("None"); txtWZPath.Text = "";
                        XML.WriteEndElement();
                        XML.WriteStartElement("PNGs");
                            XML.WriteString("None"); txtPNGPath.Text = "";
                        XML.WriteEndElement();
                        XML.WriteStartElement("Map_Renders");
                            XML.WriteString("None"); txtMapPath.Text = "";
                        XML.WriteEndElement();
                        XML.WriteStartElement("MP3s");
                            XML.WriteString("None"); txtMP3Path.Text = "";
                        XML.WriteEndElement();
                        XML.WriteStartElement("Resolve_UOLs");
                            XML.WriteValue(false); chkResolveUOL.Checked = false;
                        XML.WriteEndElement();
                        XML.WriteStartElement("Language");
                            XML.WriteValue(0); cmbLanguage.SelectedIndex = 0;
                        XML.WriteEndElement();
                    XML.WriteEndElement();
                XML.WriteEndDocument();
                XML.Close();
            }
        }
	}
}
