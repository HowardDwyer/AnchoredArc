using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
// 
// Project hull02
// Howard Dwyer
// January 2013
// 
// This project reads a hull definition from a Carlson .hul file, displays the hull, and performs
// some analysis.
//
// File format for .hul files courtesy of Gregg Carlson
//
namespace hull02
{
    public partial class Form1 : Form
    {
        //====== Fields =============================================================================
        DrawingPanel mainPanel = new DrawingPanel();

        //====== Constructor ========================================================================
        public Form1()
        {
            InitializeComponent();
            this.Text = hullConst.PROJECTTITLE;
            labelAuthor.Text = hullConst.AUTHOR;
            buttonOpenFile.Height = hullConst.BUTTONHEIGHT;
            buttonOpenFile.Width = hullConst.BUTTONWIDTH;
            buttonSave.Height = hullConst.BUTTONHEIGHT;
            buttonSave.Width = hullConst.BUTTONWIDTH;
            buttonSave.Enabled = false;
            buttonClose.Height = hullConst.BUTTONHEIGHT;
            buttonClose.Width = hullConst.BUTTONWIDTH;
            mainPanel.Enabled = true;
            mainPanel.Visible = true;

            radioButtonPlanView.Height = hullConst.RADIOBUTTONHEIGHT;
            radioButtonSideView.Height = hullConst.RADIOBUTTONHEIGHT;
            radioButtonSectionView.Height = hullConst.RADIOBUTTONHEIGHT;
            radioButton3DView.Height = hullConst.RADIOBUTTONHEIGHT;
            radioButtonPlanView.Checked = false;
            radioButtonSideView.Checked = false;
            radioButtonSectionView.Checked = false;
            radioButton3DView.Checked = true;
            groupBoxViewButtons.Visible = true;
            radioButtonPlanView.Visible = true;
            radioButtonSideView.Visible = true;
            radioButtonSectionView.Visible = true;
            radioButton3DView.Visible = true;

            checkBoxChines.Height = hullConst.CHECKBOXHEIGHT;
            checkBoxBulkheads.Height = hullConst.CHECKBOXHEIGHT;
            checkBoxStations.Height = hullConst.CHECKBOXHEIGHT;
            checkBoxWaterPlane.Height = hullConst.CHECKBOXHEIGHT;
            checkBoxNodes.Height = hullConst.CHECKBOXHEIGHT;
            checkBoxLoads.Height = hullConst.CHECKBOXHEIGHT;
            checkBoxSections.Height = hullConst.CHECKBOXHEIGHT;
            checkBoxCentroids.Height = hullConst.CHECKBOXHEIGHT;

            checkBoxChines.Checked = true;
            checkBoxBulkheads.Checked = true;
            checkBoxStations.Checked = true;
            checkBoxWaterPlane.Checked = false;
            checkBoxNodes.Checked = true;
            checkBoxLoads.Checked = false;
            checkBoxSections.Checked = false;
            checkBoxCentroids.Checked = false;

            checkBoxChines.Visible = true;
            checkBoxBulkheads.Visible = true;
            checkBoxStations.Visible = true;
            checkBoxWaterPlane.Visible = true;
            checkBoxNodes.Visible = true;
            checkBoxLoads.Visible = true;
            checkBoxSections.Visible = true;
            checkBoxCentroids.Visible = true;
        } // end of constructor

        //====== Methods ============================================================================
        private void LocateControls()
        {
            mainPanel.Top = this.Top + hullConst.PANEL1TOP;
            mainPanel.Left = this.Left + hullConst.PANEL1LEFT;
            mainPanel.Width = this.ClientRectangle.Width - 2 * hullConst.MARGIN;
            mainPanel.Height = this.ClientRectangle.Height - hullConst.MARGIN - hullConst.BOTTOMPANELHEIGHT;

            buttonOpenFile.Left = hullConst.MARGIN;
            buttonSave.Left = buttonOpenFile.Left;
            buttonClose.Left = buttonOpenFile.Left;

            buttonClose.Top = this.ClientRectangle.Height - buttonClose.Height - hullConst.MARGIN;
            buttonSave.Top = buttonClose.Top - buttonSave.Height - hullConst.GAP;
            buttonOpenFile.Top = buttonSave.Top - buttonOpenFile.Height - hullConst.GAP;

            labelAuthor.Left = this.ClientRectangle.Width - labelAuthor.Width - hullConst.MARGIN;
            labelAuthor.Top = this.ClientRectangle.Height - labelAuthor.Height - hullConst.MARGIN;

            int maxWidth = Math.Max(Math.Max(radioButtonPlanView.Width,radioButtonSectionView.Width),
                Math.Max(radioButtonSideView.Width,radioButton3DView.Width));
            groupBoxViewButtons.Width = maxWidth + 2 * hullConst.GAP;
            groupBoxViewButtons.Top = buttonOpenFile.Top-5;
            groupBoxViewButtons.Height = this.ClientRectangle.Height - groupBoxViewButtons.Top - hullConst.MARGIN;
            groupBoxViewButtons.Left = buttonOpenFile.Left + buttonOpenFile.Width + hullConst.GAP;
            radioButtonPlanView.Left = hullConst.GAP;
            radioButtonSideView.Left = radioButtonPlanView.Left;
            radioButtonSectionView.Left = radioButtonPlanView.Left;
            radioButton3DView.Left = radioButtonPlanView.Left;
            radioButtonPlanView.Top = hullConst.MARGIN;
            radioButtonSideView.Top = radioButtonPlanView.Top + hullConst.RADIOBUTTONHEIGHT + hullConst.RADIOBUTTONGAP;
            radioButtonSectionView.Top = radioButtonSideView.Top + hullConst.RADIOBUTTONHEIGHT + hullConst.RADIOBUTTONGAP;
            radioButton3DView.Top = radioButtonSectionView.Top + hullConst.RADIOBUTTONHEIGHT + hullConst.RADIOBUTTONGAP;

            maxWidth = Math.Max(Math.Max(checkBoxChines.Width, checkBoxBulkheads.Width),
                Math.Max(checkBoxStations.Width, checkBoxWaterPlane.Width));

            checkBoxChines.Left = groupBoxViewButtons.Left + groupBoxViewButtons.Width + hullConst.GAP;
            checkBoxBulkheads.Left=checkBoxChines.Left;
            checkBoxStations.Left=checkBoxChines.Left;
            checkBoxWaterPlane.Left = checkBoxChines.Left;
            checkBoxChines.Top = groupBoxViewButtons.Top+radioButtonPlanView.Top;
            checkBoxBulkheads.Top = groupBoxViewButtons.Top + radioButtonSideView.Top;
            checkBoxStations.Top = groupBoxViewButtons.Top + radioButtonSectionView.Top;
            checkBoxWaterPlane.Top = groupBoxViewButtons.Top + radioButton3DView.Top;

            checkBoxNodes.Left = checkBoxChines.Left+maxWidth + hullConst.GAP;
            checkBoxLoads.Left = checkBoxNodes.Left;
            checkBoxSections.Left = checkBoxNodes.Left;
            checkBoxCentroids.Left = checkBoxNodes.Left;
            checkBoxNodes.Top = checkBoxChines.Top;
            checkBoxLoads.Top = checkBoxBulkheads.Top;
            checkBoxSections.Top = checkBoxStations.Top;
            checkBoxCentroids.Top = checkBoxWaterPlane.Top;
            return;
        }  // end LocateControls
        
        //------------------------------------------------------------------------------------------

        //====== Event Handlers =====================================================================
        private void Form1_LocationChanged(object sender, EventArgs e)
        {
            LocateControls();
            return;
        } // end Form1_LocationChanged

        //------------------------------------------------------------------------------------------
        private void Form1_Resize(object sender, EventArgs e)
        {
            this.Width = Math.Max(this.Width, hullConst.MINWINDOWWIDTH);
            this.Height = Math.Max(this.Height, hullConst.MINWINDOWHEIGHT);

            LocateControls();
            return;
        } // end Form1_Resize

        //------------------------------------------------------------------------------------------
        private void Form1_VisibleChanged(object sender, EventArgs e)
        {
            mainPanel.Visible = this.Visible;
            return;
        }

        private void buttonClose_Click(object sender, EventArgs e)
        {
            Close();
        }// end Form1_VisibleChanged

        //------------------------------------------------------------------------------------------

    } // end class Form1
}
