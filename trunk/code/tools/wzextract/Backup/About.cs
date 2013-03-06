using System;
using System.Drawing;
using System.Windows.Forms;
using System.Diagnostics;

namespace WZextract
{
	public partial class AboutForm : Form
	{
		public AboutForm()
		{
			InitializeComponent();
			label1.Text = "WZextract " + Convert.ToString(System.Reflection.Assembly.GetExecutingAssembly().GetName().Version.Major) + "." + Convert.ToString(System.Reflection.Assembly.GetExecutingAssembly().GetName().Version.Minor);
		}
		
		void Button1Click(object sender, EventArgs e)
		{
			this.Close();
		}
		
		void LinkLabel1LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
		{
			Process.Start("http://wzextract.maststef.de");
		}
		
		void LinkLabel2LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
		{
			Process.Start("http://forum.maststef.de");
		}

	}
}
