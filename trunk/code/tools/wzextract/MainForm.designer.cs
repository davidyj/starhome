namespace WZextract
{
	partial class MainForm
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.mnuFile = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuOpen = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuQuit = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuExtras = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuHeaderInfo = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuWZCompare = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuSaveXML = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuLoadXML = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuExtract = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem3 = new System.Windows.Forms.ToolStripSeparator();
            this.findToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripTextBox1 = new System.Windows.Forms.ToolStripTextBox();
            this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripSeparator();
            this.mnuSettings = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuAbout = new System.Windows.Forms.ToolStripMenuItem();
            this.licenseToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.mnuCloseRender = new System.Windows.Forms.ToolStripMenuItem();
            this.treeView1 = new System.Windows.Forms.TreeView();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.button7 = new System.Windows.Forms.Button();
            this.button6 = new System.Windows.Forms.Button();
            this.pnlSound = new System.Windows.Forms.Panel();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.trackBar1 = new System.Windows.Forms.TrackBar();
            this.label4 = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.button5 = new System.Windows.Forms.Button();
            this.button4 = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.btnSaveMp3 = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.lstRender = new System.Windows.Forms.ListBox();
            this.chkNPC = new System.Windows.Forms.CheckBox();
            this.chkMob = new System.Windows.Forms.CheckBox();
            this.chkReactor = new System.Windows.Forms.CheckBox();
            this.chkPortal = new System.Windows.Forms.CheckBox();
            this.button2 = new System.Windows.Forms.Button();
            this.label9 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.txtType = new System.Windows.Forms.TextBox();
            this.pnlPicture = new System.Windows.Forms.Panel();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.lblUOL = new System.Windows.Forms.LinkLabel();
            this.textBox8 = new System.Windows.Forms.TextBox();
            this.renderContainer = new System.Windows.Forms.SplitContainer();
            this.picRender = new System.Windows.Forms.PictureBox();
            this.cmdCloseRender = new System.Windows.Forms.Button();
            this.cmdSaveRender = new System.Windows.Forms.Button();
            this.cmdRedrawRender = new System.Windows.Forms.Button();
            this.lstRenders = new System.Windows.Forms.ListBox();
            this.chkReactorr = new System.Windows.Forms.CheckBox();
            this.chkPortalr = new System.Windows.Forms.CheckBox();
            this.chkMobr = new System.Windows.Forms.CheckBox();
            this.chkNPCr = new System.Windows.Forms.CheckBox();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.toolStripStatusLabel1 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripStatusLabel2 = new System.Windows.Forms.ToolStripStatusLabel();
            this.toolStripProgressBar1 = new System.Windows.Forms.ToolStripProgressBar();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.splitContainer2 = new System.Windows.Forms.SplitContainer();
            this.label2 = new System.Windows.Forms.Label();
            this.treeView2 = new System.Windows.Forms.TreeView();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.fullExtractPanel = new System.Windows.Forms.Panel();
            this.label6 = new System.Windows.Forms.Label();
            this.extractCount = new System.Windows.Forms.Label();
            this.extractBar = new System.Windows.Forms.ProgressBar();
            this.extractCancel = new System.Windows.Forms.Button();
            this.extractStart = new System.Windows.Forms.Button();
            this.menuStrip1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.pnlSound.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).BeginInit();
            this.pnlPicture.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.renderContainer.Panel1.SuspendLayout();
            this.renderContainer.Panel2.SuspendLayout();
            this.renderContainer.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.picRender)).BeginInit();
            this.statusStrip1.SuspendLayout();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.splitContainer2.Panel1.SuspendLayout();
            this.splitContainer2.Panel2.SuspendLayout();
            this.splitContainer2.SuspendLayout();
            this.fullExtractPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuFile,
            this.mnuExtras,
            this.mnuAbout,
            this.mnuCloseRender});
            this.menuStrip1.LayoutStyle = System.Windows.Forms.ToolStripLayoutStyle.HorizontalStackWithOverflow;
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(846, 25);
            this.menuStrip1.TabIndex = 1;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // mnuFile
            // 
            this.mnuFile.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuOpen,
            this.mnuQuit});
            this.mnuFile.Name = "mnuFile";
            this.mnuFile.Size = new System.Drawing.Size(39, 21);
            this.mnuFile.Text = "&File";
            // 
            // mnuOpen
            // 
            this.mnuOpen.Name = "mnuOpen";
            this.mnuOpen.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
            this.mnuOpen.Size = new System.Drawing.Size(164, 22);
            this.mnuOpen.Text = "&Open...";
            this.mnuOpen.Click += new System.EventHandler(this.OpenToolStripMenuItemClick);
            // 
            // mnuQuit
            // 
            this.mnuQuit.Name = "mnuQuit";
            this.mnuQuit.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.F4)));
            this.mnuQuit.Size = new System.Drawing.Size(164, 22);
            this.mnuQuit.Text = "&Quit";
            this.mnuQuit.Click += new System.EventHandler(this.QuitToolStripMenuItemClick);
            // 
            // mnuExtras
            // 
            this.mnuExtras.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuHeaderInfo,
            this.mnuWZCompare,
            this.mnuExtract,
            this.toolStripMenuItem3,
            this.findToolStripMenuItem,
            this.toolStripTextBox1,
            this.toolStripMenuItem2,
            this.mnuSettings});
            this.mnuExtras.Name = "mnuExtras";
            this.mnuExtras.Size = new System.Drawing.Size(55, 21);
            this.mnuExtras.Text = "&Extras";
            // 
            // mnuHeaderInfo
            // 
            this.mnuHeaderInfo.Enabled = false;
            this.mnuHeaderInfo.Name = "mnuHeaderInfo";
            this.mnuHeaderInfo.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.H)));
            this.mnuHeaderInfo.Size = new System.Drawing.Size(236, 22);
            this.mnuHeaderInfo.Text = "Header information";
            this.mnuHeaderInfo.Click += new System.EventHandler(this.ShowHeaderInformationToolStripMenuItemClick);
            // 
            // mnuWZCompare
            // 
            this.mnuWZCompare.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mnuSaveXML,
            this.mnuLoadXML});
            this.mnuWZCompare.Enabled = false;
            this.mnuWZCompare.Name = "mnuWZCompare";
            this.mnuWZCompare.Size = new System.Drawing.Size(236, 22);
            this.mnuWZCompare.Text = "WZ Comparison";
            // 
            // mnuSaveXML
            // 
            this.mnuSaveXML.Enabled = false;
            this.mnuSaveXML.Name = "mnuSaveXML";
            this.mnuSaveXML.Size = new System.Drawing.Size(208, 22);
            this.mnuSaveXML.Text = "Save XML File...";
            this.mnuSaveXML.Click += new System.EventHandler(this.saveXMLFileToolStripMenuItem_Click);
            // 
            // mnuLoadXML
            // 
            this.mnuLoadXML.Enabled = false;
            this.mnuLoadXML.Name = "mnuLoadXML";
            this.mnuLoadXML.Size = new System.Drawing.Size(208, 22);
            this.mnuLoadXML.Text = "Compare to XML File...";
            this.mnuLoadXML.Click += new System.EventHandler(this.compareToXMLFileToolStripMenuItem_Click);
            // 
            // mnuExtract
            // 
            this.mnuExtract.Enabled = false;
            this.mnuExtract.Name = "mnuExtract";
            this.mnuExtract.Size = new System.Drawing.Size(236, 22);
            this.mnuExtract.Text = "Extract everything to disk";
            this.mnuExtract.Click += new System.EventHandler(this.MnuExtractClick);
            // 
            // toolStripMenuItem3
            // 
            this.toolStripMenuItem3.Name = "toolStripMenuItem3";
            this.toolStripMenuItem3.Size = new System.Drawing.Size(233, 6);
            // 
            // findToolStripMenuItem
            // 
            this.findToolStripMenuItem.Enabled = false;
            this.findToolStripMenuItem.Name = "findToolStripMenuItem";
            this.findToolStripMenuItem.Size = new System.Drawing.Size(236, 22);
            this.findToolStripMenuItem.Text = "Find in tree:";
            // 
            // toolStripTextBox1
            // 
            this.toolStripTextBox1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.toolStripTextBox1.Name = "toolStripTextBox1";
            this.toolStripTextBox1.Size = new System.Drawing.Size(100, 23);
            this.toolStripTextBox1.KeyDown += new System.Windows.Forms.KeyEventHandler(this.ToolStripTextBox1KeyDown);
            // 
            // toolStripMenuItem2
            // 
            this.toolStripMenuItem2.Name = "toolStripMenuItem2";
            this.toolStripMenuItem2.Size = new System.Drawing.Size(233, 6);
            // 
            // mnuSettings
            // 
            this.mnuSettings.Name = "mnuSettings";
            this.mnuSettings.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S)));
            this.mnuSettings.Size = new System.Drawing.Size(236, 22);
            this.mnuSettings.Text = "&Settings...";
            this.mnuSettings.Click += new System.EventHandler(this.PreferencesToolStripMenuItemClick);
            // 
            // mnuAbout
            // 
            this.mnuAbout.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.licenseToolStripMenuItem,
            this.aboutToolStripMenuItem});
            this.mnuAbout.Name = "mnuAbout";
            this.mnuAbout.Size = new System.Drawing.Size(26, 21);
            this.mnuAbout.Text = "?";
            // 
            // licenseToolStripMenuItem
            // 
            this.licenseToolStripMenuItem.Name = "licenseToolStripMenuItem";
            this.licenseToolStripMenuItem.Size = new System.Drawing.Size(118, 22);
            this.licenseToolStripMenuItem.Text = "License";
            this.licenseToolStripMenuItem.Click += new System.EventHandler(this.LicenseToolStripMenuItemClick);
            // 
            // aboutToolStripMenuItem
            // 
            this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
            this.aboutToolStripMenuItem.Size = new System.Drawing.Size(118, 22);
            this.aboutToolStripMenuItem.Text = "About";
            this.aboutToolStripMenuItem.Click += new System.EventHandler(this.AboutToolStripMenuItemClick);
            // 
            // mnuCloseRender
            // 
            this.mnuCloseRender.Name = "mnuCloseRender";
            this.mnuCloseRender.Size = new System.Drawing.Size(98, 21);
            this.mnuCloseRender.Text = "Close Render";
            this.mnuCloseRender.Visible = false;
            this.mnuCloseRender.Click += new System.EventHandler(this.closeRenderToolStripMenuItem_Click);
            // 
            // treeView1
            // 
            this.treeView1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.treeView1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.treeView1.HideSelection = false;
            this.treeView1.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.treeView1.Location = new System.Drawing.Point(0, 0);
            this.treeView1.Name = "treeView1";
            this.treeView1.Size = new System.Drawing.Size(164, 205);
            this.treeView1.TabIndex = 2;
            this.treeView1.Tag = "";
            this.treeView1.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.TreeView1AfterSelect);
            // 
            // groupBox2
            // 
            this.groupBox2.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.groupBox2.Controls.Add(this.button7);
            this.groupBox2.Controls.Add(this.button6);
            this.groupBox2.Controls.Add(this.pnlSound);
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Controls.Add(this.button1);
            this.groupBox2.Controls.Add(this.lstRender);
            this.groupBox2.Controls.Add(this.chkNPC);
            this.groupBox2.Controls.Add(this.chkMob);
            this.groupBox2.Controls.Add(this.chkReactor);
            this.groupBox2.Controls.Add(this.chkPortal);
            this.groupBox2.Controls.Add(this.button2);
            this.groupBox2.Controls.Add(this.label9);
            this.groupBox2.Controls.Add(this.label8);
            this.groupBox2.Controls.Add(this.label7);
            this.groupBox2.Controls.Add(this.txtType);
            this.groupBox2.Controls.Add(this.pnlPicture);
            this.groupBox2.Controls.Add(this.lblUOL);
            this.groupBox2.Controls.Add(this.textBox8);
            this.groupBox2.Location = new System.Drawing.Point(2, 0);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(657, 434);
            this.groupBox2.TabIndex = 3;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Data";
            // 
            // button7
            // 
            this.button7.Location = new System.Drawing.Point(9, 405);
            this.button7.Name = "button7";
            this.button7.Size = new System.Drawing.Size(52, 23);
            this.button7.TabIndex = 25;
            this.button7.Text = "to xml";
            this.button7.UseVisualStyleBackColor = true;
            this.button7.Click += new System.EventHandler(this.button7_Click);
            // 
            // button6
            // 
            this.button6.Location = new System.Drawing.Point(5, 302);
            this.button6.Name = "button6";
            this.button6.Size = new System.Drawing.Size(54, 38);
            this.button6.TabIndex = 24;
            this.button6.Text = "Extract image";
            this.button6.UseVisualStyleBackColor = true;
            this.button6.Visible = false;
            this.button6.Click += new System.EventHandler(this.Button6Click);
            // 
            // pnlSound
            // 
            this.pnlSound.AutoScroll = true;
            this.pnlSound.AutoSize = true;
            this.pnlSound.Controls.Add(this.checkBox1);
            this.pnlSound.Controls.Add(this.trackBar1);
            this.pnlSound.Controls.Add(this.label4);
            this.pnlSound.Controls.Add(this.textBox1);
            this.pnlSound.Controls.Add(this.label3);
            this.pnlSound.Controls.Add(this.button5);
            this.pnlSound.Controls.Add(this.button4);
            this.pnlSound.Controls.Add(this.button3);
            this.pnlSound.Controls.Add(this.btnSaveMp3);
            this.pnlSound.Location = new System.Drawing.Point(66, 42);
            this.pnlSound.Name = "pnlSound";
            this.pnlSound.Size = new System.Drawing.Size(380, 192);
            this.pnlSound.TabIndex = 23;
            this.pnlSound.Visible = false;
            // 
            // checkBox1
            // 
            this.checkBox1.Location = new System.Drawing.Point(192, 6);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(58, 19);
            this.checkBox1.TabIndex = 30;
            this.checkBox1.Text = "Loop";
            this.checkBox1.UseVisualStyleBackColor = true;
            // 
            // trackBar1
            // 
            this.trackBar1.Location = new System.Drawing.Point(4, 31);
            this.trackBar1.Name = "trackBar1";
            this.trackBar1.Size = new System.Drawing.Size(203, 45);
            this.trackBar1.TabIndex = 29;
            this.trackBar1.TickStyle = System.Windows.Forms.TickStyle.None;
            this.trackBar1.Scroll += new System.EventHandler(this.TrackBar1Scroll);
            // 
            // label4
            // 
            this.label4.Location = new System.Drawing.Point(213, 32);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(49, 18);
            this.label4.TabIndex = 28;
            this.label4.Text = "00:00 /";
            // 
            // textBox1
            // 
            this.textBox1.BackColor = System.Drawing.SystemColors.Window;
            this.textBox1.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBox1.Location = new System.Drawing.Point(3, 72);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.ReadOnly = true;
            this.textBox1.Size = new System.Drawing.Size(293, 117);
            this.textBox1.TabIndex = 27;
            this.textBox1.TabStop = false;
            // 
            // label3
            // 
            this.label3.Location = new System.Drawing.Point(259, 32);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(37, 18);
            this.label3.TabIndex = 26;
            this.label3.Text = "00:00";
            // 
            // button5
            // 
            this.button5.Location = new System.Drawing.Point(125, 3);
            this.button5.Name = "button5";
            this.button5.Size = new System.Drawing.Size(55, 23);
            this.button5.TabIndex = 24;
            this.button5.Text = "Stop";
            this.button5.UseVisualStyleBackColor = true;
            this.button5.Click += new System.EventHandler(this.Button5Click);
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(64, 3);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(55, 23);
            this.button4.TabIndex = 23;
            this.button4.Text = "Pause";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.Button4Click);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(3, 3);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(55, 23);
            this.button3.TabIndex = 22;
            this.button3.Text = "Play";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.Button3Click);
            // 
            // btnSaveMp3
            // 
            this.btnSaveMp3.Location = new System.Drawing.Point(256, 3);
            this.btnSaveMp3.Name = "btnSaveMp3";
            this.btnSaveMp3.Size = new System.Drawing.Size(40, 23);
            this.btnSaveMp3.TabIndex = 19;
            this.btnSaveMp3.Text = "Save";
            this.btnSaveMp3.UseVisualStyleBackColor = true;
            this.btnSaveMp3.Click += new System.EventHandler(this.BtnSaveMp3Click);
            // 
            // label1
            // 
            this.label1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(6, 194);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(590, 113);
            this.label1.TabIndex = 5;
            this.label1.Text = resources.GetString("label1.Text");
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(7, 346);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(54, 43);
            this.button1.TabIndex = 21;
            this.button1.Text = "Save image";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Visible = false;
            this.button1.Click += new System.EventHandler(this.Button1Click);
            // 
            // lstRender
            // 
            this.lstRender.FormattingEnabled = true;
            this.lstRender.ItemHeight = 12;
            this.lstRender.Items.AddRange(new object[] {
            "None",
            "Black",
            "White"});
            this.lstRender.Location = new System.Drawing.Point(6, 258);
            this.lstRender.Name = "lstRender";
            this.lstRender.Size = new System.Drawing.Size(54, 40);
            this.lstRender.TabIndex = 13;
            this.lstRender.Visible = false;
            // 
            // chkNPC
            // 
            this.chkNPC.Checked = true;
            this.chkNPC.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkNPC.Location = new System.Drawing.Point(5, 238);
            this.chkNPC.Name = "chkNPC";
            this.chkNPC.Size = new System.Drawing.Size(55, 15);
            this.chkNPC.TabIndex = 12;
            this.chkNPC.Text = "NPCs";
            this.chkNPC.UseVisualStyleBackColor = true;
            this.chkNPC.Visible = false;
            this.chkNPC.CheckedChanged += new System.EventHandler(this.ChkNPCCheckedChanged);
            // 
            // chkMob
            // 
            this.chkMob.Checked = true;
            this.chkMob.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkMob.Location = new System.Drawing.Point(5, 218);
            this.chkMob.Name = "chkMob";
            this.chkMob.Size = new System.Drawing.Size(55, 15);
            this.chkMob.TabIndex = 11;
            this.chkMob.Text = "Mob";
            this.chkMob.UseVisualStyleBackColor = true;
            this.chkMob.Visible = false;
            this.chkMob.CheckedChanged += new System.EventHandler(this.ChkMobCheckedChanged);
            // 
            // chkReactor
            // 
            this.chkReactor.Checked = true;
            this.chkReactor.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkReactor.Location = new System.Drawing.Point(5, 193);
            this.chkReactor.Name = "chkReactor";
            this.chkReactor.Size = new System.Drawing.Size(55, 19);
            this.chkReactor.TabIndex = 10;
            this.chkReactor.Text = "Reactor";
            this.chkReactor.UseVisualStyleBackColor = true;
            this.chkReactor.Visible = false;
            this.chkReactor.CheckedChanged += new System.EventHandler(this.ChkReactorCheckedChanged);
            // 
            // chkPortal
            // 
            this.chkPortal.Checked = true;
            this.chkPortal.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkPortal.Location = new System.Drawing.Point(5, 171);
            this.chkPortal.Name = "chkPortal";
            this.chkPortal.Size = new System.Drawing.Size(55, 20);
            this.chkPortal.TabIndex = 9;
            this.chkPortal.Text = "Portal";
            this.chkPortal.UseVisualStyleBackColor = true;
            this.chkPortal.Visible = false;
            this.chkPortal.CheckedChanged += new System.EventHandler(this.ChkPortalCheckedChanged);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(5, 114);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(54, 50);
            this.button2.TabIndex = 8;
            this.button2.Text = "Render this Map!";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Visible = false;
            this.button2.Click += new System.EventHandler(this.Button2Click);
            // 
            // label9
            // 
            this.label9.Location = new System.Drawing.Point(6, 64);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(55, 37);
            this.label9.TabIndex = 5;
            this.label9.Text = "Click the picture to save it!";
            this.label9.Visible = false;
            // 
            // label8
            // 
            this.label8.Location = new System.Drawing.Point(6, 44);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(50, 14);
            this.label8.TabIndex = 3;
            this.label8.Text = "Content:";
            // 
            // label7
            // 
            this.label7.Location = new System.Drawing.Point(6, 18);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(42, 17);
            this.label7.TabIndex = 1;
            this.label7.Text = "Type:";
            // 
            // txtType
            // 
            this.txtType.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.txtType.BackColor = System.Drawing.SystemColors.Window;
            this.txtType.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txtType.Location = new System.Drawing.Point(67, 18);
            this.txtType.Multiline = true;
            this.txtType.Name = "txtType";
            this.txtType.ReadOnly = true;
            this.txtType.Size = new System.Drawing.Size(584, 19);
            this.txtType.TabIndex = 0;
            // 
            // pnlPicture
            // 
            this.pnlPicture.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.pnlPicture.AutoScroll = true;
            this.pnlPicture.BackColor = System.Drawing.SystemColors.Control;
            this.pnlPicture.Controls.Add(this.pictureBox1);
            this.pnlPicture.Location = new System.Drawing.Point(67, 42);
            this.pnlPicture.Name = "pnlPicture";
            this.pnlPicture.Size = new System.Drawing.Size(584, 387);
            this.pnlPicture.TabIndex = 17;
            this.pnlPicture.Visible = false;
            // 
            // pictureBox1
            // 
            this.pictureBox1.BackColor = System.Drawing.SystemColors.Control;
            this.pictureBox1.Location = new System.Drawing.Point(3, 3);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(553, 338);
            this.pictureBox1.TabIndex = 4;
            this.pictureBox1.TabStop = false;
            this.pictureBox1.Visible = false;
            this.pictureBox1.Click += new System.EventHandler(this.PictureBox1Click);
            // 
            // lblUOL
            // 
            this.lblUOL.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.lblUOL.BackColor = System.Drawing.SystemColors.Control;
            this.lblUOL.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblUOL.LinkBehavior = System.Windows.Forms.LinkBehavior.NeverUnderline;
            this.lblUOL.Location = new System.Drawing.Point(67, 42);
            this.lblUOL.Name = "lblUOL";
            this.lblUOL.Size = new System.Drawing.Size(408, 30);
            this.lblUOL.TabIndex = 20;
            this.lblUOL.Visible = false;
            this.lblUOL.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.linkLabel1_LinkClicked);
            // 
            // textBox8
            // 
            this.textBox8.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.textBox8.BackColor = System.Drawing.SystemColors.Window;
            this.textBox8.Font = new System.Drawing.Font("Courier New", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBox8.Location = new System.Drawing.Point(67, 42);
            this.textBox8.Multiline = true;
            this.textBox8.Name = "textBox8";
            this.textBox8.ReadOnly = true;
            this.textBox8.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBox8.Size = new System.Drawing.Size(584, 387);
            this.textBox8.TabIndex = 2;
            this.textBox8.Visible = false;
            // 
            // renderContainer
            // 
            this.renderContainer.FixedPanel = System.Windows.Forms.FixedPanel.Panel2;
            this.renderContainer.IsSplitterFixed = true;
            this.renderContainer.Location = new System.Drawing.Point(606, 0);
            this.renderContainer.Name = "renderContainer";
            this.renderContainer.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // renderContainer.Panel1
            // 
            this.renderContainer.Panel1.AutoScroll = true;
            this.renderContainer.Panel1.Controls.Add(this.picRender);
            // 
            // renderContainer.Panel2
            // 
            this.renderContainer.Panel2.Controls.Add(this.cmdCloseRender);
            this.renderContainer.Panel2.Controls.Add(this.cmdSaveRender);
            this.renderContainer.Panel2.Controls.Add(this.cmdRedrawRender);
            this.renderContainer.Panel2.Controls.Add(this.lstRenders);
            this.renderContainer.Panel2.Controls.Add(this.chkReactorr);
            this.renderContainer.Panel2.Controls.Add(this.chkPortalr);
            this.renderContainer.Panel2.Controls.Add(this.chkMobr);
            this.renderContainer.Panel2.Controls.Add(this.chkNPCr);
            this.renderContainer.Size = new System.Drawing.Size(240, 207);
            this.renderContainer.SplitterDistance = 131;
            this.renderContainer.TabIndex = 0;
            this.renderContainer.TabStop = false;
            this.renderContainer.Visible = false;
            // 
            // picRender
            // 
            this.picRender.Location = new System.Drawing.Point(0, 0);
            this.picRender.Name = "picRender";
            this.picRender.Size = new System.Drawing.Size(279, 128);
            this.picRender.TabIndex = 0;
            this.picRender.TabStop = false;
            // 
            // cmdCloseRender
            // 
            this.cmdCloseRender.Location = new System.Drawing.Point(399, 34);
            this.cmdCloseRender.Name = "cmdCloseRender";
            this.cmdCloseRender.Size = new System.Drawing.Size(43, 21);
            this.cmdCloseRender.TabIndex = 7;
            this.cmdCloseRender.Text = "Close";
            this.cmdCloseRender.UseVisualStyleBackColor = true;
            this.cmdCloseRender.Click += new System.EventHandler(this.CmdCloseRenderClick);
            // 
            // cmdSaveRender
            // 
            this.cmdSaveRender.Location = new System.Drawing.Point(269, 34);
            this.cmdSaveRender.Name = "cmdSaveRender";
            this.cmdSaveRender.Size = new System.Drawing.Size(124, 21);
            this.cmdSaveRender.TabIndex = 6;
            this.cmdSaveRender.Text = "Save";
            this.cmdSaveRender.UseVisualStyleBackColor = true;
            this.cmdSaveRender.Click += new System.EventHandler(this.CmdSaveRenderClick);
            // 
            // cmdRedrawRender
            // 
            this.cmdRedrawRender.Location = new System.Drawing.Point(269, 8);
            this.cmdRedrawRender.Name = "cmdRedrawRender";
            this.cmdRedrawRender.Size = new System.Drawing.Size(173, 20);
            this.cmdRedrawRender.TabIndex = 5;
            this.cmdRedrawRender.Text = "Render with new settings";
            this.cmdRedrawRender.UseVisualStyleBackColor = true;
            this.cmdRedrawRender.Click += new System.EventHandler(this.CmdRedrawRenderClick);
            // 
            // lstRenders
            // 
            this.lstRenders.FormattingEnabled = true;
            this.lstRenders.ItemHeight = 12;
            this.lstRenders.Items.AddRange(new object[] {
            "None",
            "Black",
            "White"});
            this.lstRenders.Location = new System.Drawing.Point(157, 8);
            this.lstRenders.Name = "lstRenders";
            this.lstRenders.Size = new System.Drawing.Size(106, 52);
            this.lstRenders.TabIndex = 4;
            // 
            // chkReactorr
            // 
            this.chkReactorr.Checked = true;
            this.chkReactorr.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkReactorr.Location = new System.Drawing.Point(77, 8);
            this.chkReactorr.Name = "chkReactorr";
            this.chkReactorr.Size = new System.Drawing.Size(74, 20);
            this.chkReactorr.TabIndex = 3;
            this.chkReactorr.Text = "Reactors";
            this.chkReactorr.UseVisualStyleBackColor = true;
            this.chkReactorr.CheckedChanged += new System.EventHandler(this.ChkReactorrCheckedChanged);
            // 
            // chkPortalr
            // 
            this.chkPortalr.Checked = true;
            this.chkPortalr.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkPortalr.Location = new System.Drawing.Point(9, 10);
            this.chkPortalr.Name = "chkPortalr";
            this.chkPortalr.Size = new System.Drawing.Size(62, 18);
            this.chkPortalr.TabIndex = 2;
            this.chkPortalr.Text = "Portals";
            this.chkPortalr.UseVisualStyleBackColor = true;
            this.chkPortalr.CheckedChanged += new System.EventHandler(this.ChkPortalrCheckedChanged);
            // 
            // chkMobr
            // 
            this.chkMobr.Checked = true;
            this.chkMobr.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkMobr.Location = new System.Drawing.Point(9, 30);
            this.chkMobr.Name = "chkMobr";
            this.chkMobr.Size = new System.Drawing.Size(51, 18);
            this.chkMobr.TabIndex = 1;
            this.chkMobr.Text = "Mob";
            this.chkMobr.UseVisualStyleBackColor = true;
            this.chkMobr.CheckedChanged += new System.EventHandler(this.ChkMobrCheckedChanged);
            // 
            // chkNPCr
            // 
            this.chkNPCr.Checked = true;
            this.chkNPCr.CheckState = System.Windows.Forms.CheckState.Checked;
            this.chkNPCr.Location = new System.Drawing.Point(77, 30);
            this.chkNPCr.Name = "chkNPCr";
            this.chkNPCr.Size = new System.Drawing.Size(68, 18);
            this.chkNPCr.TabIndex = 0;
            this.chkNPCr.Text = "NPCs";
            this.chkNPCr.UseVisualStyleBackColor = true;
            this.chkNPCr.CheckedChanged += new System.EventHandler(this.ChkNPCrCheckedChanged);
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripStatusLabel1,
            this.toolStripStatusLabel2,
            this.toolStripProgressBar1});
            this.statusStrip1.Location = new System.Drawing.Point(0, 463);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(846, 22);
            this.statusStrip1.TabIndex = 4;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // toolStripStatusLabel1
            // 
            this.toolStripStatusLabel1.AutoSize = false;
            this.toolStripStatusLabel1.BorderSides = ((System.Windows.Forms.ToolStripStatusLabelBorderSides)((((System.Windows.Forms.ToolStripStatusLabelBorderSides.Left | System.Windows.Forms.ToolStripStatusLabelBorderSides.Top) 
            | System.Windows.Forms.ToolStripStatusLabelBorderSides.Right) 
            | System.Windows.Forms.ToolStripStatusLabelBorderSides.Bottom)));
            this.toolStripStatusLabel1.Name = "toolStripStatusLabel1";
            this.toolStripStatusLabel1.Size = new System.Drawing.Size(300, 17);
            // 
            // toolStripStatusLabel2
            // 
            this.toolStripStatusLabel2.AutoSize = false;
            this.toolStripStatusLabel2.BorderSides = ((System.Windows.Forms.ToolStripStatusLabelBorderSides)((((System.Windows.Forms.ToolStripStatusLabelBorderSides.Left | System.Windows.Forms.ToolStripStatusLabelBorderSides.Top) 
            | System.Windows.Forms.ToolStripStatusLabelBorderSides.Right) 
            | System.Windows.Forms.ToolStripStatusLabelBorderSides.Bottom)));
            this.toolStripStatusLabel2.Name = "toolStripStatusLabel2";
            this.toolStripStatusLabel2.Size = new System.Drawing.Size(200, 17);
            // 
            // toolStripProgressBar1
            // 
            this.toolStripProgressBar1.Name = "toolStripProgressBar1";
            this.toolStripProgressBar1.Size = new System.Drawing.Size(100, 16);
            this.toolStripProgressBar1.Visible = false;
            // 
            // splitContainer1
            // 
            this.splitContainer1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.splitContainer1.BackColor = System.Drawing.SystemColors.Control;
            this.splitContainer1.ForeColor = System.Drawing.SystemColors.ControlText;
            this.splitContainer1.Location = new System.Drawing.Point(0, 25);
            this.splitContainer1.Name = "splitContainer1";
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.splitContainer2);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.groupBox2);
            this.splitContainer1.Size = new System.Drawing.Size(846, 437);
            this.splitContainer1.SplitterDistance = 171;
            this.splitContainer1.TabIndex = 5;
            // 
            // splitContainer2
            // 
            this.splitContainer2.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.splitContainer2.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.splitContainer2.Location = new System.Drawing.Point(7, 3);
            this.splitContainer2.Name = "splitContainer2";
            this.splitContainer2.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer2.Panel1
            // 
            this.splitContainer2.Panel1.Controls.Add(this.treeView1);
            // 
            // splitContainer2.Panel2
            // 
            this.splitContainer2.Panel2.Controls.Add(this.label2);
            this.splitContainer2.Panel2.Controls.Add(this.treeView2);
            this.splitContainer2.Size = new System.Drawing.Size(164, 426);
            this.splitContainer2.SplitterDistance = 208;
            this.splitContainer2.TabIndex = 4;
            // 
            // label2
            // 
            this.label2.Location = new System.Drawing.Point(5, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(100, 16);
            this.label2.TabIndex = 4;
            this.label2.Text = "Image file content:";
            // 
            // treeView2
            // 
            this.treeView2.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.treeView2.HideSelection = false;
            this.treeView2.Location = new System.Drawing.Point(0, 18);
            this.treeView2.Name = "treeView2";
            this.treeView2.Size = new System.Drawing.Size(164, 193);
            this.treeView2.TabIndex = 3;
            this.treeView2.AfterSelect += new System.Windows.Forms.TreeViewEventHandler(this.TreeView2AfterSelect);
            // 
            // timer1
            // 
            this.timer1.Tick += new System.EventHandler(this.Timer1Tick);
            // 
            // fullExtractPanel
            // 
            this.fullExtractPanel.Controls.Add(this.label6);
            this.fullExtractPanel.Controls.Add(this.extractCount);
            this.fullExtractPanel.Controls.Add(this.extractBar);
            this.fullExtractPanel.Controls.Add(this.extractCancel);
            this.fullExtractPanel.Controls.Add(this.extractStart);
            this.fullExtractPanel.Location = new System.Drawing.Point(307, 0);
            this.fullExtractPanel.Name = "fullExtractPanel";
            this.fullExtractPanel.Size = new System.Drawing.Size(281, 145);
            this.fullExtractPanel.TabIndex = 6;
            this.fullExtractPanel.Visible = false;
            // 
            // label6
            // 
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.Location = new System.Drawing.Point(29, 9);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(203, 34);
            this.label6.TabIndex = 4;
            this.label6.Text = "Full Extract Control Panel";
            // 
            // extractCount
            // 
            this.extractCount.Location = new System.Drawing.Point(29, 72);
            this.extractCount.Name = "extractCount";
            this.extractCount.Size = new System.Drawing.Size(203, 20);
            this.extractCount.TabIndex = 3;
            this.extractCount.Text = "progress";
            // 
            // extractBar
            // 
            this.extractBar.Location = new System.Drawing.Point(32, 46);
            this.extractBar.Name = "extractBar";
            this.extractBar.Size = new System.Drawing.Size(200, 18);
            this.extractBar.TabIndex = 2;
            // 
            // extractCancel
            // 
            this.extractCancel.Location = new System.Drawing.Point(184, 97);
            this.extractCancel.Name = "extractCancel";
            this.extractCancel.Size = new System.Drawing.Size(48, 24);
            this.extractCancel.TabIndex = 1;
            this.extractCancel.Text = "Cancel";
            this.extractCancel.UseVisualStyleBackColor = true;
            this.extractCancel.Click += new System.EventHandler(this.ExtractCancelClick);
            // 
            // extractStart
            // 
            this.extractStart.Location = new System.Drawing.Point(32, 97);
            this.extractStart.Name = "extractStart";
            this.extractStart.Size = new System.Drawing.Size(146, 24);
            this.extractStart.TabIndex = 0;
            this.extractStart.Text = "Start";
            this.extractStart.UseVisualStyleBackColor = true;
            this.extractStart.Click += new System.EventHandler(this.ExtractStartClick);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(846, 485);
            this.Controls.Add(this.fullExtractPanel);
            this.Controls.Add(this.renderContainer);
            this.Controls.Add(this.splitContainer1);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.menuStrip1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "MainForm";
            this.Text = "WZextract";
            this.WindowState = System.Windows.Forms.FormWindowState.Maximized;
            this.Load += new System.EventHandler(this.MainForm_Load);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.pnlSound.ResumeLayout(false);
            this.pnlSound.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.trackBar1)).EndInit();
            this.pnlPicture.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.renderContainer.Panel1.ResumeLayout(false);
            this.renderContainer.Panel2.ResumeLayout(false);
            this.renderContainer.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.picRender)).EndInit();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.ResumeLayout(false);
            this.splitContainer2.Panel1.ResumeLayout(false);
            this.splitContainer2.Panel2.ResumeLayout(false);
            this.splitContainer2.ResumeLayout(false);
            this.fullExtractPanel.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

		}
		private System.Windows.Forms.Button button6;
		private System.Windows.Forms.Panel fullExtractPanel;
		private System.Windows.Forms.Label extractCount;
		private System.Windows.Forms.ProgressBar extractBar;
		private System.Windows.Forms.Button extractCancel;
		private System.Windows.Forms.Button extractStart;
		private System.Windows.Forms.Label label6;
		private System.Windows.Forms.ToolStripMenuItem mnuExtract;
		private System.Windows.Forms.CheckBox checkBox1;
		private System.Windows.Forms.TrackBar trackBar1;
		private System.Windows.Forms.Timer timer1;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.TextBox textBox1;
		private System.Windows.Forms.Button button4;
		private System.Windows.Forms.Button button5;
		private System.Windows.Forms.Panel pnlSound;
		private System.Windows.Forms.Button button3;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Button button1;
		private System.Windows.Forms.Button cmdCloseRender;
		private System.Windows.Forms.Button cmdSaveRender;
		private System.Windows.Forms.Button cmdRedrawRender;
		private System.Windows.Forms.ListBox lstRenders;
		private System.Windows.Forms.PictureBox picRender;
		private System.Windows.Forms.SplitContainer renderContainer;
		private System.Windows.Forms.CheckBox chkNPCr;
		private System.Windows.Forms.CheckBox chkMobr;
		private System.Windows.Forms.CheckBox chkPortalr;
		private System.Windows.Forms.CheckBox chkReactorr;
		private System.Windows.Forms.ToolStripMenuItem licenseToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem mnuSettings;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem2;
		private System.Windows.Forms.ToolStripMenuItem findToolStripMenuItem;
		private System.Windows.Forms.ToolStripTextBox toolStripTextBox1;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.SplitContainer splitContainer2;
		private System.Windows.Forms.TreeView treeView2;
		private System.Windows.Forms.ListBox lstRender;
		private System.Windows.Forms.CheckBox chkReactor;
		private System.Windows.Forms.CheckBox chkMob;
		private System.Windows.Forms.CheckBox chkNPC;
		private System.Windows.Forms.ToolStripMenuItem mnuHeaderInfo;
		private System.Windows.Forms.CheckBox chkPortal;
		private System.Windows.Forms.Button button2;
        private System.Windows.Forms.ToolStripProgressBar toolStripProgressBar1;
		private System.Windows.Forms.Label label9;
		private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel2;
		private System.Windows.Forms.PictureBox pictureBox1;
		private System.Windows.Forms.TextBox textBox8;
		private System.Windows.Forms.Label label8;
		private System.Windows.Forms.Label label7;
		private System.Windows.Forms.TextBox txtType;
		private System.Windows.Forms.ToolStripMenuItem mnuExtras;
		private System.Windows.Forms.ToolStripStatusLabel toolStripStatusLabel1;
		private System.Windows.Forms.SplitContainer splitContainer1;
		private System.Windows.Forms.StatusStrip statusStrip1;
		private System.Windows.Forms.GroupBox groupBox2;
		private System.Windows.Forms.TreeView treeView1;
		private System.Windows.Forms.ToolStripMenuItem mnuQuit;
		private System.Windows.Forms.ToolStripMenuItem mnuOpen;
		private System.Windows.Forms.ToolStripMenuItem mnuAbout;
		private System.Windows.Forms.ToolStripMenuItem mnuFile;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.Panel pnlPicture;
        private System.Windows.Forms.Button btnSaveMp3;
        private System.Windows.Forms.LinkLabel lblUOL;
        private System.Windows.Forms.ToolStripMenuItem mnuWZCompare;
        private System.Windows.Forms.ToolStripMenuItem mnuSaveXML;
        private System.Windows.Forms.ToolStripMenuItem mnuLoadXML;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem3;
        private System.Windows.Forms.ToolStripMenuItem mnuCloseRender;
        private System.Windows.Forms.Button button7;
	}
}
