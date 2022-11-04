using System.Windows.Forms;
using System;
using System.Data;
using System.Data.Odbc;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
using System.Data.SqlClient;
using System.Data.Common;

namespace MDBtoExcel
{
    public partial class CMDBtoExcelDlg : Form
    {
        private void UpdateCheckState()
        {
            int nIdx = 0;
            m_arrFindIdx.Clear();
            foreach (ListViewItem item in listView_Columns.Items)
            {
                if (item.Checked)
                {
                    m_arrColumns[nIdx].CheckState = true;
                    m_arrFindIdx.Add(nIdx);
                }
                nIdx++;
            }
        }
        public CMDBtoExcelDlg()
        {
            InitializeComponent();
            pictureBox_LOGO.Image = Properties.Resources.logo;
            pictureBox_LOGO.SizeMode = PictureBoxSizeMode.StretchImage;
            m_arrColumns = new List<CColumn>();
            m_arrFindIdx = new List<int>();
        }

        private void BTN_OPEN_Click(object sender, EventArgs e)
        {
            OpenFileDialog OpenDialog = new OpenFileDialog();
            OpenDialog.Filter = "MDB files (*.mdb)|*.mdb";
            if (OpenDialog.ShowDialog() == DialogResult.OK)
            {
                if(m_strPathName != OpenDialog.FileName)
                {
                    textBox_FileName.Text = OpenDialog.SafeFileName;
                    m_strPathName = OpenDialog.FileName;

                    button_Connect.Enabled = true;
                    textBox_PassWord.Enabled = true;
                    comboBox_TableList.Enabled = true;
                }

                else if(m_strPathName == OpenDialog.FileName)
                {
                    MessageBox.Show("이미 개방된 DB 입니다.");
                }

                else
                {
                    textBox_FileName.Text = OpenDialog.SafeFileName;
                    m_strPathName = OpenDialog.FileName;
                    if(m_odbcConnection != null)
                    {
                        m_odbcConnection.Close();
                    }
                    listView_Columns.Items.Clear();
                    comboBox_TableList.Items.Clear();

                    button_Connect.Enabled = false;
                    textBox_PassWord.Enabled = false;
                    comboBox_TableList.Enabled = false;
                }
                textBox_PassWord.Text = "B1594C47";
            }
        }

        private void BTN_CONNECT_Click(object sender, EventArgs e)
        {
            string connectionString =
            "Driver={Microsoft Access Driver (*.mdb, *.accdb)};"
            + "Dbq=" + m_strPathName +";" 
            + "Pwd=" + textBox_PassWord.Text +";";

            m_odbcConnection = new OdbcConnection(connectionString);
            try
            {
                m_odbcConnection.Open(); 
                MessageBox.Show("연결되었습니다.");
                
                m_odbcCommand = new OdbcCommand();
                m_odbcCommand.Connection = m_odbcConnection;
            }
            catch (Exception ex)
            {
                MessageBox.Show("연결에 실패하였습니다.");
            }

            DataTable dataTable = new DataTable();
            dataTable = m_odbcConnection.GetSchema("Tables");
            foreach (DataRow row in dataTable.Rows)
            {
                comboBox_TableList.Items.Add(row["TABLE_NAME"].ToString());
            }
            comboBox_TableList.SelectedIndex = 0;

            try
            {
                m_odbcCommand.CommandText = "select count(*) from " + comboBox_TableList.Text + ";";
                m_odbcDataReader = m_odbcCommand.ExecuteReader();
                m_odbcDataReader.Read();
                textBox_TotalRows.Text = m_odbcDataReader.GetString(0);
                m_odbcDataReader.Close();

                listView_Columns.Columns.Add("Table Name", listView_Columns.Width);
                listView_Columns.Columns[0].Width 
                    = listView_Columns.Width - 4 -SystemInformation.VerticalScrollBarWidth;

                m_odbcCommand.CommandText = "select * from " + comboBox_TableList.Text + ";";
                m_odbcDataReader = m_odbcCommand.ExecuteReader();
                int nCount = m_odbcDataReader.FieldCount;
                listView_Columns.BeginUpdate();
                string strName;
                for (int nColumn = 0; nColumn < nCount; nColumn++)
                {
                    strName = m_odbcDataReader.GetName(nColumn);
                    listView_Columns.Items.Add(strName);
                    m_arrColumns.Add(new CColumn());
                    m_arrColumns[nColumn].OriginName = strName;
                    m_arrColumns[nColumn].ChangeName = strName;
                    m_arrColumns[nColumn].CheckState = false;
                }
                m_odbcDataReader.Close();
                listView_Columns.EndUpdate();
            }
            catch (Exception ex)
            {
                textBox_TotalRows.Text = "Error Table";
            }   
        }

        private void comboBox_TableList_SelectionChangeCommitted(object sender, EventArgs e)
        {
            try
            {
                m_odbcCommand.CommandText = "select count(*) from " + comboBox_TableList.Text + ";";
                m_odbcDataReader = m_odbcCommand.ExecuteReader();
                m_odbcDataReader.Read();
                textBox_TotalRows.Text = m_odbcDataReader.GetString(0);
                m_odbcDataReader.Close();

                listView_Columns.Clear();
                m_arrColumns.Clear();
                listView_Columns.Columns.Add("Table Name", listView_Columns.Width);
                listView_Columns.Columns[0].Width
                    = listView_Columns.Width - 4 - SystemInformation.VerticalScrollBarWidth;

                m_odbcCommand.CommandText = "select * from " + comboBox_TableList.Text + ";";
                m_odbcDataReader = m_odbcCommand.ExecuteReader();
                int nCount = m_odbcDataReader.FieldCount;
                string strName;
                listView_Columns.BeginUpdate();
                for (int nColumn = 0; nColumn < nCount; nColumn++)
                {
                    strName = m_odbcDataReader.GetName(nColumn);
                    listView_Columns.Items.Add(strName);
                    m_arrColumns.Add(new CColumn());
                    m_arrColumns[nColumn].OriginName = strName;
                    m_arrColumns[nColumn].ChangeName = strName;
                    m_arrColumns[nColumn].CheckState = false;
                }
                m_odbcDataReader.Close();
                listView_Columns.EndUpdate();
            }
            catch (Exception ex)
            {
                textBox_TotalRows.Text = "Error Table";
            }
        }

        private void listView_Columns_ColumnClick(object sender, ColumnClickEventArgs e)
        {
            int nIdx = 0;
            foreach(ListViewItem item in listView_Columns.Items)
            {
                if(item.Checked)
                {
                    item.Checked = false;
                    m_arrColumns[nIdx].CheckState = false;
                }
                else
                {
                    item.Checked = true;
                    m_arrColumns[nIdx].CheckState = true;
                }
                
            }
        }

        private void button_ChangeColumn_Click(object sender, EventArgs e)
        {
            UpdateCheckState();
            ColChangeFormDlg dlgChange = new ColChangeFormDlg(this);
            if (dlgChange.ShowDialog() == DialogResult.OK)
            {

            }
        }
    }
}