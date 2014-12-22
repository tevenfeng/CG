namespace ToneMapping
{
    partial class mainForm
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.button_importPic = new System.Windows.Forms.Button();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.mytoolStripStatusLabel = new System.Windows.Forms.ToolStripStatusLabel();
            this.pictureBox_original = new System.Windows.Forms.PictureBox();
            this.pictureBox_result = new System.Windows.Forms.PictureBox();
            this.button_ToneMapping = new System.Windows.Forms.Button();
            this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            this.textBox_b = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.statusStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_original)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_result)).BeginInit();
            this.SuspendLayout();
            // 
            // button_importPic
            // 
            this.button_importPic.Location = new System.Drawing.Point(303, 12);
            this.button_importPic.Name = "button_importPic";
            this.button_importPic.Size = new System.Drawing.Size(75, 23);
            this.button_importPic.TabIndex = 0;
            this.button_importPic.Text = "导入图片";
            this.button_importPic.UseVisualStyleBackColor = true;
            this.button_importPic.Click += new System.EventHandler(this.button_importPic_Click);
            // 
            // statusStrip1
            // 
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.mytoolStripStatusLabel});
            this.statusStrip1.Location = new System.Drawing.Point(0, 842);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(1092, 22);
            this.statusStrip1.TabIndex = 1;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // mytoolStripStatusLabel
            // 
            this.mytoolStripStatusLabel.Name = "mytoolStripStatusLabel";
            this.mytoolStripStatusLabel.Size = new System.Drawing.Size(0, 17);
            // 
            // pictureBox_original
            // 
            this.pictureBox_original.Location = new System.Drawing.Point(13, 59);
            this.pictureBox_original.Name = "pictureBox_original";
            this.pictureBox_original.Size = new System.Drawing.Size(512, 768);
            this.pictureBox_original.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.pictureBox_original.TabIndex = 2;
            this.pictureBox_original.TabStop = false;
            // 
            // pictureBox_result
            // 
            this.pictureBox_result.Location = new System.Drawing.Point(558, 59);
            this.pictureBox_result.Name = "pictureBox_result";
            this.pictureBox_result.Size = new System.Drawing.Size(512, 768);
            this.pictureBox_result.SizeMode = System.Windows.Forms.PictureBoxSizeMode.AutoSize;
            this.pictureBox_result.TabIndex = 3;
            this.pictureBox_result.TabStop = false;
            // 
            // button_ToneMapping
            // 
            this.button_ToneMapping.Location = new System.Drawing.Point(701, 12);
            this.button_ToneMapping.Name = "button_ToneMapping";
            this.button_ToneMapping.Size = new System.Drawing.Size(82, 23);
            this.button_ToneMapping.TabIndex = 4;
            this.button_ToneMapping.Text = "ToneMapping";
            this.button_ToneMapping.UseVisualStyleBackColor = true;
            this.button_ToneMapping.Click += new System.EventHandler(this.button_ToneMapping_Click);
            // 
            // textBox_b
            // 
            this.textBox_b.Location = new System.Drawing.Point(558, 14);
            this.textBox_b.Name = "textBox_b";
            this.textBox_b.Size = new System.Drawing.Size(100, 21);
            this.textBox_b.TabIndex = 5;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(421, 17);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(131, 12);
            this.label1.TabIndex = 6;
            this.label1.Text = "请输入bias公式的b值：";
            // 
            // mainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1092, 864);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textBox_b);
            this.Controls.Add(this.button_ToneMapping);
            this.Controls.Add(this.pictureBox_result);
            this.Controls.Add(this.pictureBox_original);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.button_importPic);
            this.Name = "mainForm";
            this.Text = "ToneMapping";
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_original)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_result)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button button_importPic;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.ToolStripStatusLabel mytoolStripStatusLabel;
        private System.Windows.Forms.PictureBox pictureBox_original;
        private System.Windows.Forms.PictureBox pictureBox_result;
        private System.Windows.Forms.Button button_ToneMapping;
        private System.ComponentModel.BackgroundWorker backgroundWorker1;
        private System.Windows.Forms.TextBox textBox_b;
        private System.Windows.Forms.Label label1;
    }
}

