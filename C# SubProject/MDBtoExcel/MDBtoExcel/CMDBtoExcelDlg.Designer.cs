using System.Data.Odbc;

public class CColumn
{
    private string m_strOriginName;
    public string OriginName
    {
        get { return m_strOriginName; }
        set { m_strOriginName = value; }
    }

    private string m_strChangeName;
    public string ChangeName
    {
        get { return m_strChangeName; }
        set { m_strChangeName = value; }
    }

    private int m_nType;
    public int Type
    {
        get { return m_nType; }
        set { m_nType = value; }
    }

    private bool m_bCheckState;
    public bool CheckState
    {
        get { return m_bCheckState; }
        set { m_bCheckState = value; }
    }

    
}


namespace MDBtoExcel
{
    partial class CMDBtoExcelDlg
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.button_Open = new System.Windows.Forms.Button();
            this.button_Connect = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.textBox_FileName = new System.Windows.Forms.TextBox();
            this.textBox_PassWord = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.comboBox_TableList = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.textBox_TotalRows = new System.Windows.Forms.TextBox();
            this.listView_Columns = new System.Windows.Forms.ListView();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.pictureBox_LOGO = new System.Windows.Forms.PictureBox();
            this.button_ChangeColumn = new System.Windows.Forms.Button();
            this.button_convert_Excel = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_LOGO)).BeginInit();
            this.SuspendLayout();
            // 
            // button_Open
            // 
            this.button_Open.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.button_Open.Font = new System.Drawing.Font("Consolas", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.button_Open.Location = new System.Drawing.Point(17, 108);
            this.button_Open.Name = "button_Open";
            this.button_Open.Size = new System.Drawing.Size(140, 40);
            this.button_Open.TabIndex = 0;
            this.button_Open.Text = "OPEN";
            this.button_Open.UseVisualStyleBackColor = true;
            this.button_Open.Click += new System.EventHandler(this.BTN_OPEN_Click);
            // 
            // button_Connect
            // 
            this.button_Connect.Enabled = false;
            this.button_Connect.Font = new System.Drawing.Font("Consolas", 14.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.button_Connect.Location = new System.Drawing.Point(17, 161);
            this.button_Connect.Name = "button_Connect";
            this.button_Connect.Size = new System.Drawing.Size(140, 40);
            this.button_Connect.TabIndex = 1;
            this.button_Connect.Text = "CONNECT";
            this.button_Connect.UseVisualStyleBackColor = true;
            this.button_Connect.Click += new System.EventHandler(this.BTN_CONNECT_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Consolas", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.label1.Location = new System.Drawing.Point(175, 108);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(70, 15);
            this.label1.TabIndex = 2;
            this.label1.Text = "File Name";
            // 
            // textBox_FileName
            // 
            this.textBox_FileName.Location = new System.Drawing.Point(175, 126);
            this.textBox_FileName.Name = "textBox_FileName";
            this.textBox_FileName.ReadOnly = true;
            this.textBox_FileName.Size = new System.Drawing.Size(117, 23);
            this.textBox_FileName.TabIndex = 3;
            // 
            // textBox_PassWord
            // 
            this.textBox_PassWord.Enabled = false;
            this.textBox_PassWord.Location = new System.Drawing.Point(175, 178);
            this.textBox_PassWord.Name = "textBox_PassWord";
            this.textBox_PassWord.Size = new System.Drawing.Size(117, 23);
            this.textBox_PassWord.TabIndex = 4;
            this.textBox_PassWord.UseSystemPasswordChar = true;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Consolas", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.label2.Location = new System.Drawing.Point(175, 159);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(21, 15);
            this.label2.TabIndex = 5;
            this.label2.Text = "PW";
            // 
            // comboBox_TableList
            // 
            this.comboBox_TableList.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.comboBox_TableList.FormattingEnabled = true;
            this.comboBox_TableList.ImeMode = System.Windows.Forms.ImeMode.Off;
            this.comboBox_TableList.Location = new System.Drawing.Point(17, 233);
            this.comboBox_TableList.Name = "comboBox_TableList";
            this.comboBox_TableList.Size = new System.Drawing.Size(140, 23);
            this.comboBox_TableList.TabIndex = 6;
            this.comboBox_TableList.SelectionChangeCommitted += new System.EventHandler(this.comboBox_TableList_SelectionChangeCommitted);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Consolas", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.label3.Location = new System.Drawing.Point(17, 212);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(49, 15);
            this.label3.TabIndex = 7;
            this.label3.Text = "Tables";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Consolas", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point);
            this.label4.Location = new System.Drawing.Point(175, 212);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(77, 15);
            this.label4.TabIndex = 8;
            this.label4.Text = "Total Rows";
            // 
            // textBox_TotalRows
            // 
            this.textBox_TotalRows.Location = new System.Drawing.Point(175, 233);
            this.textBox_TotalRows.Name = "textBox_TotalRows";
            this.textBox_TotalRows.ReadOnly = true;
            this.textBox_TotalRows.Size = new System.Drawing.Size(117, 23);
            this.textBox_TotalRows.TabIndex = 9;
            this.textBox_TotalRows.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // listView_Columns
            // 
            this.listView_Columns.CheckBoxes = true;
            this.listView_Columns.GridLines = true;
            this.listView_Columns.Location = new System.Drawing.Point(17, 262);
            this.listView_Columns.Name = "listView_Columns";
            this.listView_Columns.Size = new System.Drawing.Size(140, 133);
            this.listView_Columns.TabIndex = 10;
            this.listView_Columns.UseCompatibleStateImageBehavior = false;
            this.listView_Columns.View = System.Windows.Forms.View.Details;
            this.listView_Columns.ColumnClick += new System.Windows.Forms.ColumnClickEventHandler(this.listView_Columns_ColumnClick);
            // 
            // progressBar1
            // 
            this.progressBar1.Location = new System.Drawing.Point(17, 402);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(275, 36);
            this.progressBar1.TabIndex = 11;
            // 
            // pictureBox_LOGO
            // 
            this.pictureBox_LOGO.Location = new System.Drawing.Point(17, 11);
            this.pictureBox_LOGO.Name = "pictureBox_LOGO";
            this.pictureBox_LOGO.Size = new System.Drawing.Size(275, 91);
            this.pictureBox_LOGO.TabIndex = 12;
            this.pictureBox_LOGO.TabStop = false;
            // 
            // button_ChangeColumn
            // 
            this.button_ChangeColumn.Location = new System.Drawing.Point(175, 262);
            this.button_ChangeColumn.Name = "button_ChangeColumn";
            this.button_ChangeColumn.Size = new System.Drawing.Size(117, 32);
            this.button_ChangeColumn.TabIndex = 13;
            this.button_ChangeColumn.Text = "Change Column";
            this.button_ChangeColumn.UseVisualStyleBackColor = true;
            this.button_ChangeColumn.Click += new System.EventHandler(this.button_ChangeColumn_Click);
            // 
            // button_convert_Excel
            // 
            this.button_convert_Excel.Location = new System.Drawing.Point(175, 300);
            this.button_convert_Excel.Name = "button_convert_Excel";
            this.button_convert_Excel.Size = new System.Drawing.Size(117, 32);
            this.button_convert_Excel.TabIndex = 14;
            this.button_convert_Excel.Text = "Convert";
            this.button_convert_Excel.UseVisualStyleBackColor = true;
            this.button_convert_Excel.Click += new System.EventHandler(this.button_convert_Excel_Click);
            // 
            // CMDBtoExcelDlg
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(306, 450);
            this.Controls.Add(this.button_convert_Excel);
            this.Controls.Add(this.button_ChangeColumn);
            this.Controls.Add(this.pictureBox_LOGO);
            this.Controls.Add(this.progressBar1);
            this.Controls.Add(this.listView_Columns);
            this.Controls.Add(this.textBox_TotalRows);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.comboBox_TableList);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.textBox_PassWord);
            this.Controls.Add(this.textBox_FileName);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.button_Connect);
            this.Controls.Add(this.button_Open);
            this.Name = "CMDBtoExcelDlg";
            this.Text = "MDB to Excel";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_LOGO)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private string m_strPathName;
        private string m_strSelectedCol;

        private OdbcConnection m_odbcConnection;
        private OdbcCommand m_odbcCommand;
        private OdbcDataReader m_odbcDataReader;
        

        private Label label1;
        private Label label2;
        private Label label3;
        private Label label4;

        private Button button_Open;
        private Button button_Connect;    
        private TextBox textBox_FileName;
        private TextBox textBox_PassWord;
        private TextBox textBox_TotalRows;
        private ComboBox comboBox_TableList;
        private ProgressBar progressBar1;
        private PictureBox pictureBox_LOGO;
        private Button button_ChangeColumn;

        public ListView listView_Columns;
        public List<CColumn> m_arrColumns;
        public List<int> m_arrFindIdx;
        private Button button_convert_Excel;
    }
}