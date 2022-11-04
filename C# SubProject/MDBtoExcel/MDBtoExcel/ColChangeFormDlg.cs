using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MDBtoExcel
{
    public partial class ColChangeFormDlg : Form
    {
        public ColChangeFormDlg(CMDBtoExcelDlg parent)
        {
            InitializeComponent();
            m_dlgMain = parent;
            listView_ChangeName.Columns.Add("Origin Name", listView_ChangeName.Width / 2);
            listView_ChangeName.Columns.Add("Change Name", listView_ChangeName.Width / 2);

            for(int nCount =0; nCount < m_dlgMain.m_arrFindIdx.Count(); nCount++)
            {
                listView_ChangeName.Items
                    .Add(m_dlgMain.m_arrColumns[m_dlgMain.m_arrFindIdx[nCount]].OriginName);
                listView_ChangeName.Items[nCount].SubItems
                    .Add(m_dlgMain.m_arrColumns[m_dlgMain.m_arrFindIdx[nCount]].ChangeName);
            }
        }

        private void listView_ChangeName_MouseClick(object sender, MouseEventArgs e)
        {

        }

        private void listView_ChangeName_KeyDown(object sender, KeyEventArgs e)
        {

        }
    }
}
