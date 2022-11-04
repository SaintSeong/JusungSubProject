namespace MDBtoExcel
{
    partial class ColChangeFormDlg
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.listView_ChangeName = new System.Windows.Forms.ListView();
            this.button_OK = new System.Windows.Forms.Button();
            this.button_Cancel = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // listView_ChangeName
            // 
            this.listView_ChangeName.GridLines = true;
            this.listView_ChangeName.FullRowSelect = true;
            this.listView_ChangeName.Location = new System.Drawing.Point(12, 12);
            this.listView_ChangeName.Name = "listView_ChangeName";
            this.listView_ChangeName.Size = new System.Drawing.Size(358, 183);
            this.listView_ChangeName.TabIndex = 0;
            this.listView_ChangeName.UseCompatibleStateImageBehavior = false;
            this.listView_ChangeName.View = System.Windows.Forms.View.Details;
            this.listView_ChangeName.KeyDown += new System.Windows.Forms.KeyEventHandler(this.listView_ChangeName_KeyDown);
            this.listView_ChangeName.MouseClick += new System.Windows.Forms.MouseEventHandler(this.listView_ChangeName_MouseClick);
            // 
            // button_OK
            // 
            this.button_OK.Location = new System.Drawing.Point(12, 209);
            this.button_OK.Name = "button_OK";
            this.button_OK.Size = new System.Drawing.Size(140, 49);
            this.button_OK.TabIndex = 1;
            this.button_OK.Text = "OK";
            this.button_OK.UseVisualStyleBackColor = true;
            // 
            // button_Cancel
            // 
            this.button_Cancel.Location = new System.Drawing.Point(230, 209);
            this.button_Cancel.Name = "button_Cancel";
            this.button_Cancel.Size = new System.Drawing.Size(140, 49);
            this.button_Cancel.TabIndex = 2;
            this.button_Cancel.Text = "Cancle";
            this.button_Cancel.UseVisualStyleBackColor = true;
            // 
            // ColChangeFormDlg
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(377, 270);
            this.Controls.Add(this.button_Cancel);
            this.Controls.Add(this.button_OK);
            this.Controls.Add(this.listView_ChangeName);
            this.Name = "ColChangeFormDlg";
            this.Text = "Column Change";
            this.ResumeLayout(false);

        }

        #endregion

        private ListView listView_ChangeName;
        private Button button_OK;
        private Button button_Cancel;
        private readonly CMDBtoExcelDlg m_dlgMain;
    }
}