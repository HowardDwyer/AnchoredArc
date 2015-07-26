namespace hull02
{
    partial class Form1
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
            this.buttonOpenFile = new System.Windows.Forms.Button();
            this.buttonSave = new System.Windows.Forms.Button();
            this.buttonClose = new System.Windows.Forms.Button();
            this.labelAuthor = new System.Windows.Forms.Label();
            this.radioButtonPlanView = new System.Windows.Forms.RadioButton();
            this.radioButtonSideView = new System.Windows.Forms.RadioButton();
            this.radioButtonSectionView = new System.Windows.Forms.RadioButton();
            this.radioButton3DView = new System.Windows.Forms.RadioButton();
            this.groupBoxViewButtons = new System.Windows.Forms.GroupBox();
            this.checkBoxChines = new System.Windows.Forms.CheckBox();
            this.checkBoxBulkheads = new System.Windows.Forms.CheckBox();
            this.checkBoxStations = new System.Windows.Forms.CheckBox();
            this.checkBoxWaterPlane = new System.Windows.Forms.CheckBox();
            this.checkBoxNodes = new System.Windows.Forms.CheckBox();
            this.checkBoxLoads = new System.Windows.Forms.CheckBox();
            this.checkBoxSections = new System.Windows.Forms.CheckBox();
            this.checkBoxCentroids = new System.Windows.Forms.CheckBox();
            this.groupBoxViewButtons.SuspendLayout();
            this.SuspendLayout();
            // 
            // buttonOpenFile
            // 
            this.buttonOpenFile.Location = new System.Drawing.Point(12, 297);
            this.buttonOpenFile.Name = "buttonOpenFile";
            this.buttonOpenFile.Size = new System.Drawing.Size(108, 36);
            this.buttonOpenFile.TabIndex = 0;
            this.buttonOpenFile.Text = "Open File";
            this.buttonOpenFile.UseVisualStyleBackColor = true;
            // 
            // buttonSave
            // 
            this.buttonSave.Location = new System.Drawing.Point(12, 339);
            this.buttonSave.Name = "buttonSave";
            this.buttonSave.Size = new System.Drawing.Size(104, 31);
            this.buttonSave.TabIndex = 1;
            this.buttonSave.Text = "Save";
            this.buttonSave.UseVisualStyleBackColor = true;
            // 
            // buttonClose
            // 
            this.buttonClose.Location = new System.Drawing.Point(12, 376);
            this.buttonClose.Name = "buttonClose";
            this.buttonClose.Size = new System.Drawing.Size(102, 26);
            this.buttonClose.TabIndex = 2;
            this.buttonClose.Text = "Close";
            this.buttonClose.UseVisualStyleBackColor = true;
            this.buttonClose.Click += new System.EventHandler(this.buttonClose_Click);
            // 
            // labelAuthor
            // 
            this.labelAuthor.AutoSize = true;
            this.labelAuthor.ForeColor = System.Drawing.Color.Gray;
            this.labelAuthor.Location = new System.Drawing.Point(610, 389);
            this.labelAuthor.Name = "labelAuthor";
            this.labelAuthor.Size = new System.Drawing.Size(60, 13);
            this.labelAuthor.TabIndex = 3;
            this.labelAuthor.Text = "labelAuthor";
            // 
            // radioButtonPlanView
            // 
            this.radioButtonPlanView.AutoSize = true;
            this.radioButtonPlanView.Location = new System.Drawing.Point(18, 35);
            this.radioButtonPlanView.Name = "radioButtonPlanView";
            this.radioButtonPlanView.Size = new System.Drawing.Size(72, 17);
            this.radioButtonPlanView.TabIndex = 0;
            this.radioButtonPlanView.TabStop = true;
            this.radioButtonPlanView.Text = "Plan View";
            this.radioButtonPlanView.UseVisualStyleBackColor = true;
            // 
            // radioButtonSideView
            // 
            this.radioButtonSideView.AutoSize = true;
            this.radioButtonSideView.Location = new System.Drawing.Point(18, 58);
            this.radioButtonSideView.Name = "radioButtonSideView";
            this.radioButtonSideView.Size = new System.Drawing.Size(69, 17);
            this.radioButtonSideView.TabIndex = 1;
            this.radioButtonSideView.TabStop = true;
            this.radioButtonSideView.Text = "SideView";
            this.radioButtonSideView.UseVisualStyleBackColor = true;
            // 
            // radioButtonSectionView
            // 
            this.radioButtonSectionView.AutoSize = true;
            this.radioButtonSectionView.Location = new System.Drawing.Point(18, 90);
            this.radioButtonSectionView.Name = "radioButtonSectionView";
            this.radioButtonSectionView.Size = new System.Drawing.Size(87, 17);
            this.radioButtonSectionView.TabIndex = 2;
            this.radioButtonSectionView.TabStop = true;
            this.radioButtonSectionView.Text = "Section View";
            this.radioButtonSectionView.UseVisualStyleBackColor = true;
            // 
            // radioButton3DView
            // 
            this.radioButton3DView.AutoSize = true;
            this.radioButton3DView.Location = new System.Drawing.Point(18, 117);
            this.radioButton3DView.Name = "radioButton3DView";
            this.radioButton3DView.Size = new System.Drawing.Size(65, 17);
            this.radioButton3DView.TabIndex = 3;
            this.radioButton3DView.TabStop = true;
            this.radioButton3DView.Text = "3D View";
            this.radioButton3DView.UseVisualStyleBackColor = true;
            // 
            // groupBoxViewButtons
            // 
            this.groupBoxViewButtons.Controls.Add(this.radioButton3DView);
            this.groupBoxViewButtons.Controls.Add(this.radioButtonSectionView);
            this.groupBoxViewButtons.Controls.Add(this.radioButtonSideView);
            this.groupBoxViewButtons.Controls.Add(this.radioButtonPlanView);
            this.groupBoxViewButtons.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.groupBoxViewButtons.Location = new System.Drawing.Point(138, 255);
            this.groupBoxViewButtons.Name = "groupBoxViewButtons";
            this.groupBoxViewButtons.Size = new System.Drawing.Size(110, 146);
            this.groupBoxViewButtons.TabIndex = 4;
            this.groupBoxViewButtons.TabStop = false;
            // 
            // checkBoxChines
            // 
            this.checkBoxChines.AutoSize = true;
            this.checkBoxChines.Location = new System.Drawing.Point(274, 282);
            this.checkBoxChines.Name = "checkBoxChines";
            this.checkBoxChines.Size = new System.Drawing.Size(58, 17);
            this.checkBoxChines.TabIndex = 5;
            this.checkBoxChines.Text = "Chines";
            this.checkBoxChines.UseVisualStyleBackColor = true;
            // 
            // checkBoxBulkheads
            // 
            this.checkBoxBulkheads.AutoSize = true;
            this.checkBoxBulkheads.Location = new System.Drawing.Point(274, 308);
            this.checkBoxBulkheads.Name = "checkBoxBulkheads";
            this.checkBoxBulkheads.Size = new System.Drawing.Size(76, 17);
            this.checkBoxBulkheads.TabIndex = 6;
            this.checkBoxBulkheads.Text = "Bulkheads";
            this.checkBoxBulkheads.UseVisualStyleBackColor = true;
            // 
            // checkBoxStations
            // 
            this.checkBoxStations.AutoSize = true;
            this.checkBoxStations.Location = new System.Drawing.Point(274, 331);
            this.checkBoxStations.Name = "checkBoxStations";
            this.checkBoxStations.Size = new System.Drawing.Size(64, 17);
            this.checkBoxStations.TabIndex = 7;
            this.checkBoxStations.Text = "Stations";
            this.checkBoxStations.UseVisualStyleBackColor = true;
            // 
            // checkBoxWaterPlane
            // 
            this.checkBoxWaterPlane.AutoSize = true;
            this.checkBoxWaterPlane.Location = new System.Drawing.Point(274, 354);
            this.checkBoxWaterPlane.Name = "checkBoxWaterPlane";
            this.checkBoxWaterPlane.Size = new System.Drawing.Size(85, 17);
            this.checkBoxWaterPlane.TabIndex = 8;
            this.checkBoxWaterPlane.Text = "Water Plane";
            this.checkBoxWaterPlane.UseVisualStyleBackColor = true;
            // 
            // checkBoxNodes
            // 
            this.checkBoxNodes.AutoSize = true;
            this.checkBoxNodes.Location = new System.Drawing.Point(390, 282);
            this.checkBoxNodes.Name = "checkBoxNodes";
            this.checkBoxNodes.Size = new System.Drawing.Size(57, 17);
            this.checkBoxNodes.TabIndex = 9;
            this.checkBoxNodes.Text = "Nodes";
            this.checkBoxNodes.UseVisualStyleBackColor = true;
            // 
            // checkBoxLoads
            // 
            this.checkBoxLoads.AutoSize = true;
            this.checkBoxLoads.Location = new System.Drawing.Point(390, 305);
            this.checkBoxLoads.Name = "checkBoxLoads";
            this.checkBoxLoads.Size = new System.Drawing.Size(55, 17);
            this.checkBoxLoads.TabIndex = 10;
            this.checkBoxLoads.Text = "Loads";
            this.checkBoxLoads.UseVisualStyleBackColor = true;
            // 
            // checkBoxSections
            // 
            this.checkBoxSections.AutoSize = true;
            this.checkBoxSections.Location = new System.Drawing.Point(390, 331);
            this.checkBoxSections.Name = "checkBoxSections";
            this.checkBoxSections.Size = new System.Drawing.Size(67, 17);
            this.checkBoxSections.TabIndex = 11;
            this.checkBoxSections.Text = "Sections";
            this.checkBoxSections.UseVisualStyleBackColor = true;
            // 
            // checkBoxCentroids
            // 
            this.checkBoxCentroids.AutoSize = true;
            this.checkBoxCentroids.Location = new System.Drawing.Point(390, 354);
            this.checkBoxCentroids.Name = "checkBoxCentroids";
            this.checkBoxCentroids.Size = new System.Drawing.Size(70, 17);
            this.checkBoxCentroids.TabIndex = 12;
            this.checkBoxCentroids.Text = "Centroids";
            this.checkBoxCentroids.UseVisualStyleBackColor = true;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(657, 409);
            this.Controls.Add(this.checkBoxCentroids);
            this.Controls.Add(this.checkBoxSections);
            this.Controls.Add(this.checkBoxLoads);
            this.Controls.Add(this.checkBoxNodes);
            this.Controls.Add(this.checkBoxWaterPlane);
            this.Controls.Add(this.checkBoxStations);
            this.Controls.Add(this.checkBoxBulkheads);
            this.Controls.Add(this.checkBoxChines);
            this.Controls.Add(this.groupBoxViewButtons);
            this.Controls.Add(this.labelAuthor);
            this.Controls.Add(this.buttonClose);
            this.Controls.Add(this.buttonSave);
            this.Controls.Add(this.buttonOpenFile);
            this.Name = "Form1";
            this.Text = "Form1";
            this.LocationChanged += new System.EventHandler(this.Form1_LocationChanged);
            this.VisibleChanged += new System.EventHandler(this.Form1_VisibleChanged);
            this.Resize += new System.EventHandler(this.Form1_Resize);
            this.groupBoxViewButtons.ResumeLayout(false);
            this.groupBoxViewButtons.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button buttonOpenFile;
        private System.Windows.Forms.Button buttonSave;
        private System.Windows.Forms.Button buttonClose;
        private System.Windows.Forms.Label labelAuthor;
        private System.Windows.Forms.RadioButton radioButtonPlanView;
        private System.Windows.Forms.RadioButton radioButtonSideView;
        private System.Windows.Forms.RadioButton radioButtonSectionView;
        private System.Windows.Forms.RadioButton radioButton3DView;
        private System.Windows.Forms.GroupBox groupBoxViewButtons;
        private System.Windows.Forms.CheckBox checkBoxChines;
        private System.Windows.Forms.CheckBox checkBoxBulkheads;
        private System.Windows.Forms.CheckBox checkBoxStations;
        private System.Windows.Forms.CheckBox checkBoxWaterPlane;
        private System.Windows.Forms.CheckBox checkBoxNodes;
        private System.Windows.Forms.CheckBox checkBoxLoads;
        private System.Windows.Forms.CheckBox checkBoxSections;
        private System.Windows.Forms.CheckBox checkBoxCentroids;

    }
}

