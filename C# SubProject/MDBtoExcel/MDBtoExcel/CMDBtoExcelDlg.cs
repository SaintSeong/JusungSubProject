using System.Windows.Forms;
using System;
using System.Data;
using System.Data.Odbc;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
using System.Data.Common;
using SpreadsheetLight;
using System.Text;
using DocumentFormat;
using DocumentFormat.OpenXml;
using DocumentFormat.OpenXml.Spreadsheet;
using DocumentFormat.OpenXml.Wordprocessing;
using System.Reflection.PortableExecutable;
using HorizontalAlignmentValues = DocumentFormat.OpenXml.Spreadsheet.HorizontalAlignmentValues;

namespace MDBtoExcel
{
    public partial class CMDBtoExcelDlg : Form
    {
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
                if (m_strPathName != OpenDialog.FileName)
                {
                    textBox_FileName.Text = OpenDialog.SafeFileName;
                    m_strPathName = OpenDialog.FileName;

                    button_Connect.Enabled = true;
                    textBox_PassWord.Enabled = true;
                    comboBox_TableList.Enabled = true;
                }

                else if (m_strPathName == OpenDialog.FileName)
                {
                    MessageBox.Show("이미 개방된 DB 입니다.");
                }

                else
                {
                    textBox_FileName.Text = OpenDialog.SafeFileName;
                    m_strPathName = OpenDialog.FileName;
                    if (m_odbcConnection != null)
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
            + "Dbq=" + m_strPathName + ";"
            + "Pwd=" + textBox_PassWord.Text + ";";

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
                    = listView_Columns.Width - 4 - SystemInformation.VerticalScrollBarWidth;

                m_odbcCommand.CommandText = "select * from " + comboBox_TableList.Text + ";";
                m_odbcDataReader = m_odbcCommand.ExecuteReader();

                DataTable schemaTable = m_odbcDataReader.GetSchemaTable();
                listView_Columns.BeginUpdate();
                string strName;
                int nDataType;
                int nRow = 0;
                foreach (DataRow row in schemaTable.Rows)
                {
                    strName = Convert.ToString(row["ColumnName"]);
                    nDataType = Convert.ToInt32(row["ProviderType"]);
                    listView_Columns.Items.Add(strName);

                    m_arrColumns.Add(new CColumn());
                    m_arrColumns[nRow].OriginName = strName;
                    m_arrColumns[nRow].ChangeName = strName;
                    m_arrColumns[nRow].Type = nDataType;
                    m_arrColumns[nRow].CheckState = false;

                    nRow++;
                }
                listView_Columns.EndUpdate();
                m_odbcDataReader.Close();
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
                listView_Columns.Clear();
                m_arrColumns.Clear();

                m_odbcCommand.CommandText = "select count(*) from " + comboBox_TableList.Text + ";";
                m_odbcDataReader = m_odbcCommand.ExecuteReader();
                m_odbcDataReader.Read();
                textBox_TotalRows.Text = m_odbcDataReader.GetString(0);
                m_odbcDataReader.Close();

                listView_Columns.Columns.Add("Table Name", listView_Columns.Width);
                listView_Columns.Columns[0].Width
                    = listView_Columns.Width - 4 - SystemInformation.VerticalScrollBarWidth;

                m_odbcCommand.CommandText = "select * from " + comboBox_TableList.Text + ";";
                m_odbcDataReader = m_odbcCommand.ExecuteReader();

                DataTable schemaTable = m_odbcDataReader.GetSchemaTable();
                listView_Columns.BeginUpdate();
                string strName;
                int nDataType;
                int nRow = 0;
                foreach (DataRow row in schemaTable.Rows)
                {
                    strName = Convert.ToString(row["ColumnName"]);
                    nDataType = Convert.ToInt32(row["ProviderType"]);
                    listView_Columns.Items.Add(strName);

                    m_arrColumns.Add(new CColumn());
                    m_arrColumns[nRow].OriginName = strName;
                    m_arrColumns[nRow].ChangeName = strName;
                    m_arrColumns[nRow].Type = nDataType;
                    m_arrColumns[nRow].CheckState = false;

                    nRow++;
                }
                listView_Columns.EndUpdate();
                m_odbcDataReader.Close();
            }
            catch (Exception ex)
            {
                textBox_TotalRows.Text = "Error Table";
            }
        }

        private void listView_Columns_ColumnClick(object sender, ColumnClickEventArgs e)
        {
            int nIdx = 0;
            foreach (ListViewItem item in listView_Columns.Items)
            {
                if (item.Checked)
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

        private void button_convert_Excel_Click(object sender, EventArgs e)
        {
            UpdateCheckState();
            StringConnect();
            if (m_strSelectedCol != null)
            {
                SaveFileDialog dlgSave = new SaveFileDialog();
                dlgSave.Filter = "xlsx files (*.xlsx)|*.xlsx";
                if (dlgSave.ShowDialog() == DialogResult.OK)
                {
                    SLDocument excel = new SLDocument();
                    m_odbcCommand.CommandText = "select " + m_strSelectedCol + " from "
                        + comboBox_TableList.Text + ";";
                    m_odbcDataReader = m_odbcCommand.ExecuteReader();
                    int nColCount = m_odbcDataReader.FieldCount;

                    // 엑셀 헤더 입력
                    SLStyle Colstyle = excel.CreateStyle();
                    Colstyle.Alignment.Horizontal = HorizontalAlignmentValues.Center;
                    Colstyle.Fill.SetPattern(PatternValues.Solid
                        , System.Drawing.Color.Black
                        , System.Drawing.Color.White);
                    Colstyle.Font.Bold = true;
                    Colstyle.Font.FontColor = System.Drawing.Color.White;
                    Colstyle.Border.TopBorder.BorderStyle = BorderStyleValues.Medium;
                    Colstyle.Border.TopBorder.Color = System.Drawing.Color.White;
                    Colstyle.Border.LeftBorder.BorderStyle = BorderStyleValues.Medium;
                    Colstyle.Border.LeftBorder.Color = System.Drawing.Color.White;
                    Colstyle.Border.RightBorder.BorderStyle = BorderStyleValues.Medium;
                    Colstyle.Border.RightBorder.Color = System.Drawing.Color.White;
                    Colstyle.Border.BottomBorder.BorderStyle = BorderStyleValues.Medium;
                    Colstyle.Border.BottomBorder.Color = System.Drawing.Color.White;
                    for (int nIdx = 0; nIdx < nColCount; nIdx++)
                    {
                        excel.SetCellValue(1, nIdx + 1, m_odbcDataReader.GetName(nIdx));
                        excel.SetCellStyle(1, nIdx + 1, Colstyle);
                    }

                    // 엑셀 데이터 입력
                    int nRow = 2;
                    SLStyle IntStyle = excel.CreateStyle();
                    IntStyle.Alignment.Horizontal = HorizontalAlignmentValues.Center;
                    SLStyle StringStyle = excel.CreateStyle();
                    StringStyle.SetHorizontalAlignment(HorizontalAlignmentValues.Left);
                    StringStyle.SetWrapText(true); // Set Multiple Lines
                    while (m_odbcDataReader.Read())
                    {
                        for (int nIdx = 0; nIdx < nColCount; nIdx++)
                        {
                            if (m_arrColumns[m_arrFindIdx[nIdx]].Type == 10)
                            {
                                excel.SetColumnWidth(nRow, nIdx + 1, 15);
                                excel.SetCellValue(nRow, nIdx + 1, m_odbcDataReader.GetInt32(nIdx));
                                excel.SetCellStyle(nRow, nIdx + 1, IntStyle);
                            }
                            else if (m_arrColumns[m_arrFindIdx[nIdx]].Type == 13)
                            {
                                
                                excel.SetColumnWidth(nRow, nIdx + 1, 30);
                                excel.SetCellValue(nRow, nIdx + 1, m_odbcDataReader.GetString(nIdx));
                                excel.SetCellStyle(nRow, nIdx + 1, StringStyle);
                            }
                            else
                            {
                                excel.SetColumnWidth(nRow, nIdx + 1, 30);
                                excel.SetCellValue(nRow, nIdx + 1, m_odbcDataReader.GetString(nIdx));
                                excel.SetCellStyle(nRow, nIdx + 1, StringStyle);
                            }
                        }
                        nRow++;
                    }
                    // 사용 하는 셀만 그룹화 설정
                    SLPageSettings ps = excel.GetPageSettings();
                    ps.View = SheetViewValues.PageBreakPreview;
                    excel.SetPageSettings(ps);
                    excel.SaveAs(dlgSave.FileName);
                    m_odbcDataReader.Close();
                }
            }
        }
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

        private void StringConnect()
        {
            m_strSelectedCol = null;
            for (int nIdx = 0; nIdx < m_arrFindIdx.Count(); nIdx++)
            {
                m_strSelectedCol += m_arrColumns[m_arrFindIdx[nIdx]].OriginName;
                m_strSelectedCol += ",";
            }

            if (m_strSelectedCol != null)
            {
                StringBuilder strReplace = new StringBuilder(m_strSelectedCol);
                strReplace[m_strSelectedCol.Length - 1] = ' ';
                m_strSelectedCol = strReplace.ToString();
            }
        }
    }
}