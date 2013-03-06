namespace WZextract
{
	partial class PrefForm
	{
		private System.ComponentModel.IContainer components = null;
		
		protected override void Dispose(bool disposing)
		{
			if (disposing) {
				if (components != null) {
					components.Dispose();
				}
			}
			base.Dispose(disposing);
		}

		private void InitializeComponent()
		{
			this.groupBox1 = new System.Windows.Forms.GroupBox();
			this.cmdMP3Path = new System.Windows.Forms.Button();
			this.txtMP3Path = new System.Windows.Forms.TextBox();
			this.label5 = new System.Windows.Forms.Label();
			this.cmdMapPath = new System.Windows.Forms.Button();
			this.cmdPNGPath = new System.Windows.Forms.Button();
			this.cmdWZPath = new System.Windows.Forms.Button();
			this.txtMapPath = new System.Windows.Forms.TextBox();
			this.txtPNGPath = new System.Windows.Forms.TextBox();
			this.txtWZPath = new System.Windows.Forms.TextBox();
			this.label3 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.label1 = new System.Windows.Forms.Label();
			this.groupBox2 = new System.Windows.Forms.GroupBox();
			this.label4 = new System.Windows.Forms.Label();
			this.cmbLanguage = new System.Windows.Forms.ComboBox();
			this.checkBox2 = new System.Windows.Forms.CheckBox();
			this.chkResolveUOL = new System.Windows.Forms.CheckBox();
			this.cmdSave = new System.Windows.Forms.Button();
			this.cmdCancel = new System.Windows.Forms.Button();
			this.groupBox1.SuspendLayout();
			this.groupBox2.SuspendLayout();
			this.SuspendLayout();
			// 
			// groupBox1
			// 
			this.groupBox1.Controls.Add(this.cmdMP3Path);
			this.groupBox1.Controls.Add(this.txtMP3Path);
			this.groupBox1.Controls.Add(this.label5);
			this.groupBox1.Controls.Add(this.cmdMapPath);
			this.groupBox1.Controls.Add(this.cmdPNGPath);
			this.groupBox1.Controls.Add(this.cmdWZPath);
			this.groupBox1.Controls.Add(this.txtMapPath);
			this.groupBox1.Controls.Add(this.txtPNGPath);
			this.groupBox1.Controls.Add(this.txtWZPath);
			this.groupBox1.Controls.Add(this.label3);
			this.groupBox1.Controls.Add(this.label2);
			this.groupBox1.Controls.Add(this.label1);
			this.groupBox1.Location = new System.Drawing.Point(12, 12);
			this.groupBox1.Name = "groupBox1";
			this.groupBox1.Size = new System.Drawing.Size(483, 126);
			this.groupBox1.TabIndex = 0;
			this.groupBox1.TabStop = false;
			this.groupBox1.Text = "Directories";
			// 
			// cmdMP3Path
			// 
			this.cmdMP3Path.Location = new System.Drawing.Point(417, 96);
			this.cmdMP3Path.Name = "cmdMP3Path";
			this.cmdMP3Path.Size = new System.Drawing.Size(60, 20);
			this.cmdMP3Path.TabIndex = 11;
			this.cmdMP3Path.Text = "Browse...";
			this.cmdMP3Path.UseVisualStyleBackColor = true;
			this.cmdMP3Path.Click += new System.EventHandler(this.button6_Click);
			// 
			// txtMP3Path
			// 
			this.txtMP3Path.Location = new System.Drawing.Point(118, 97);
			this.txtMP3Path.Name = "txtMP3Path";
			this.txtMP3Path.Size = new System.Drawing.Size(292, 20);
			this.txtMP3Path.TabIndex = 10;
			// 
			// label5
			// 
			this.label5.Location = new System.Drawing.Point(11, 105);
			this.label5.Name = "label5";
			this.label5.Size = new System.Drawing.Size(80, 14);
			this.label5.TabIndex = 9;
			this.label5.Text = "MP3s";
			// 
			// cmdMapPath
			// 
			this.cmdMapPath.Location = new System.Drawing.Point(417, 70);
			this.cmdMapPath.Name = "cmdMapPath";
			this.cmdMapPath.Size = new System.Drawing.Size(60, 20);
			this.cmdMapPath.TabIndex = 8;
			this.cmdMapPath.Text = "Browse...";
			this.cmdMapPath.UseVisualStyleBackColor = true;
			this.cmdMapPath.Click += new System.EventHandler(this.Button5Click);
			// 
			// cmdPNGPath
			// 
			this.cmdPNGPath.Location = new System.Drawing.Point(417, 45);
			this.cmdPNGPath.Name = "cmdPNGPath";
			this.cmdPNGPath.Size = new System.Drawing.Size(60, 19);
			this.cmdPNGPath.TabIndex = 7;
			this.cmdPNGPath.Text = "Browse...";
			this.cmdPNGPath.UseVisualStyleBackColor = true;
			this.cmdPNGPath.Click += new System.EventHandler(this.Button4Click);
			// 
			// cmdWZPath
			// 
			this.cmdWZPath.Location = new System.Drawing.Point(417, 19);
			this.cmdWZPath.Name = "cmdWZPath";
			this.cmdWZPath.Size = new System.Drawing.Size(60, 20);
			this.cmdWZPath.TabIndex = 6;
			this.cmdWZPath.Text = "Browse...";
			this.cmdWZPath.UseVisualStyleBackColor = true;
			this.cmdWZPath.Click += new System.EventHandler(this.Button3Click);
			// 
			// txtMapPath
			// 
			this.txtMapPath.Location = new System.Drawing.Point(118, 71);
			this.txtMapPath.Name = "txtMapPath";
			this.txtMapPath.Size = new System.Drawing.Size(292, 20);
			this.txtMapPath.TabIndex = 5;
			// 
			// txtPNGPath
			// 
			this.txtPNGPath.Location = new System.Drawing.Point(118, 45);
			this.txtPNGPath.Name = "txtPNGPath";
			this.txtPNGPath.Size = new System.Drawing.Size(293, 20);
			this.txtPNGPath.TabIndex = 4;
			// 
			// txtWZPath
			// 
			this.txtWZPath.Location = new System.Drawing.Point(118, 19);
			this.txtWZPath.Name = "txtWZPath";
			this.txtWZPath.Size = new System.Drawing.Size(293, 20);
			this.txtWZPath.TabIndex = 3;
			// 
			// label3
			// 
			this.label3.Location = new System.Drawing.Point(11, 79);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(80, 14);
			this.label3.TabIndex = 2;
			this.label3.Text = "Map Renders";
			// 
			// label2
			// 
			this.label2.Location = new System.Drawing.Point(11, 53);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(97, 15);
			this.label2.TabIndex = 1;
			this.label2.Text = "PNGs";
			// 
			// label1
			// 
			this.label1.Location = new System.Drawing.Point(11, 27);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(101, 16);
			this.label1.TabIndex = 0;
			this.label1.Text = "WZ files";
			// 
			// groupBox2
			// 
			this.groupBox2.Controls.Add(this.label4);
			this.groupBox2.Controls.Add(this.cmbLanguage);
			this.groupBox2.Controls.Add(this.checkBox2);
			this.groupBox2.Controls.Add(this.chkResolveUOL);
			this.groupBox2.Location = new System.Drawing.Point(13, 144);
			this.groupBox2.Name = "groupBox2";
			this.groupBox2.Size = new System.Drawing.Size(482, 48);
			this.groupBox2.TabIndex = 1;
			this.groupBox2.TabStop = false;
			this.groupBox2.Text = "Settings";
			// 
			// label4
			// 
			this.label4.Location = new System.Drawing.Point(212, 21);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(113, 13);
			this.label4.TabIndex = 0;
			this.label4.Text = "Language :";
			this.label4.TextAlign = System.Drawing.ContentAlignment.TopRight;
			// 
			// cmbLanguage
			// 
			this.cmbLanguage.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
			this.cmbLanguage.FormattingEnabled = true;
			this.cmbLanguage.Items.AddRange(new object[] {
									"English"});
			this.cmbLanguage.Location = new System.Drawing.Point(329, 18);
			this.cmbLanguage.Name = "cmbLanguage";
			this.cmbLanguage.Size = new System.Drawing.Size(147, 21);
			this.cmbLanguage.TabIndex = 1;
			// 
			// checkBox2
			// 
			this.checkBox2.Location = new System.Drawing.Point(118, 19);
			this.checkBox2.Name = "checkBox2";
			this.checkBox2.Size = new System.Drawing.Size(88, 20);
			this.checkBox2.TabIndex = 1;
			this.checkBox2.Text = "Sort content";
			this.checkBox2.UseVisualStyleBackColor = true;
			this.checkBox2.Visible = false;
			// 
			// chkResolveUOL
			// 
			this.chkResolveUOL.Location = new System.Drawing.Point(11, 19);
			this.chkResolveUOL.Name = "chkResolveUOL";
			this.chkResolveUOL.Size = new System.Drawing.Size(158, 21);
			this.chkResolveUOL.TabIndex = 0;
			this.chkResolveUOL.Text = "Resolve UOLs";
			this.chkResolveUOL.UseVisualStyleBackColor = true;
			// 
			// cmdSave
			// 
			this.cmdSave.Location = new System.Drawing.Point(297, 198);
			this.cmdSave.Name = "cmdSave";
			this.cmdSave.Size = new System.Drawing.Size(126, 21);
			this.cmdSave.TabIndex = 2;
			this.cmdSave.Text = "Save";
			this.cmdSave.UseVisualStyleBackColor = true;
			this.cmdSave.Click += new System.EventHandler(this.Button1Click);
			// 
			// cmdCancel
			// 
			this.cmdCancel.Location = new System.Drawing.Point(429, 198);
			this.cmdCancel.Name = "cmdCancel";
			this.cmdCancel.Size = new System.Drawing.Size(63, 21);
			this.cmdCancel.TabIndex = 3;
			this.cmdCancel.Text = "Cancel";
			this.cmdCancel.UseVisualStyleBackColor = true;
			this.cmdCancel.Click += new System.EventHandler(this.Button2Click);
			// 
			// PrefForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(507, 231);
			this.Controls.Add(this.cmdCancel);
			this.Controls.Add(this.cmdSave);
			this.Controls.Add(this.groupBox2);
			this.Controls.Add(this.groupBox1);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
			this.Name = "PrefForm";
			this.ShowInTaskbar = false;
			this.Text = "Settings";
			this.TopMost = true;
			this.Load += new System.EventHandler(this.PrefForm_Load);
			this.groupBox1.ResumeLayout(false);
			this.groupBox1.PerformLayout();
			this.groupBox2.ResumeLayout(false);
			this.ResumeLayout(false);
		}
		private System.Windows.Forms.CheckBox checkBox2;
		private System.Windows.Forms.TextBox txtWZPath;
		private System.Windows.Forms.TextBox txtPNGPath;
		private System.Windows.Forms.TextBox txtMapPath;
		private System.Windows.Forms.Button cmdWZPath;
		private System.Windows.Forms.Button cmdPNGPath;
		private System.Windows.Forms.Button cmdMapPath;
		private System.Windows.Forms.CheckBox chkResolveUOL;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.Button cmdCancel;
		private System.Windows.Forms.Button cmdSave;
		private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.ComboBox cmbLanguage;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button cmdMP3Path;
        private System.Windows.Forms.TextBox txtMP3Path;
        private System.Windows.Forms.Label label5;
	}
}
