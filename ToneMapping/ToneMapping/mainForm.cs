using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ToneMapping
{
    public partial class mainForm : Form
    {
        Bitmap myBmp = null;
        string bmpPath = null;
        Color[,] myColor = new Color[1000, 1000];
        RGB[,] myRGB = new RGB[1000, 1000];
        //double b = 2;

        public mainForm()
        {
            InitializeComponent();
        }

        private void button_importPic_Click(object sender, EventArgs e)                                //载入图片
        {
            OpenFileDialog myFiledialog = new OpenFileDialog();
            myFiledialog.Filter = "位图文件(*.bmp)|*.bmp";

            if (myFiledialog.ShowDialog() == DialogResult.OK)
            {
                this.bmpPath = myFiledialog.FileName;
                mytoolStripStatusLabel.Text = this.bmpPath;
                try
                {
                    myBmp = new Bitmap(this.bmpPath);
                    pictureBox_original.ImageLocation = this.bmpPath;
                    for (int i = 0; i < myBmp.Height; i++)
                    {
                        for (int j = 0; j < myBmp.Width; j++)
                        {
                            myRGB[j, i] = new RGB();
                        }
                    }                    
                }
                catch (Exception excep)
                {
                    //Console.WriteLine(excep.ToString());
                    MessageBox.Show(this, excep.ToString());
                }
            }
        }

        private void button_ToneMapping_Click(object sender, EventArgs e)                               //ToneMapping算法
        {
            //b = int.Parse(textBox_b.Text);
            myBmp = new Bitmap(this.bmpPath);
            for (int i = 0;i < myBmp.Height; i++)
            {
                for (int j = 0; j < myBmp.Width; j++)
                {
                    myRGB[j, i].R = myBmp.GetPixel(j, i).R;
                    myRGB[j, i].G = myBmp.GetPixel(j, i).G;
                    myRGB[j, i].B = myBmp.GetPixel(j, i).B;
                }
            }

            for (int i = 0; i < myBmp.Height; i++)
            {
                for (int j = 0; j < myBmp.Width; j++)
                {
                    double Y = 0.212649 * myRGB[j, i].R + 0.715169 * myRGB[j, i].G + 0.072182 * myRGB[j, i].B;

                    double ave_Y = Y;
                    double Lw = Y, ave_L = ave_Y;
                    double Ld = Map(Lw);
                    Ld = Contrast(Lw,ave_L,Ld);

                    int temp_B = (int)(Math.Pow((myRGB[j, i].B / Lw), 1.2) * Ld);
                    int temp_G = (int)(Math.Pow((myRGB[j, i].G / Lw), 1.2) * Ld);
                    int temp_R = (int)(Math.Pow((myRGB[j, i].R / Lw), 1.2) * Ld);

                    temp_B = (temp_B > 255) ? 255 : temp_B;
                    temp_G = (temp_G > 255) ? 255 : temp_G;
                    temp_R = (temp_R > 255) ? 255 : temp_R;

                    myColor[j, i] = Color.FromArgb(temp_R,temp_G,temp_B);
                    myBmp.SetPixel(j, i, myColor[j, i]);
                }
            }

            pictureBox_result.Image = myBmp;
            myBmp.Save("mybmp.bmp");
        }

        private double Map(double Lw)
        {
            int Ldmax = 255;
            int Lwmax = 255;
            double b = double.Parse(textBox_b.Text);
            //double b = 10;
            double exposure = 1;

            double Ld = exposure * Ldmax * (Math.Log(Lw+1)/ (Math.Log(2 + 8 * Math.Pow(1.0 * Lw / Lwmax, (Math.Log(b) / Math.Log(0.5)))))) / Math.Log10(Lwmax + 1);
            return Ld;
        }

        private double Contrast(double Lw,double ave_L,double Ld)
        {
            double c = 0.8;
            if (ave_L == 0) ave_L = 1;

            double R = Ld * Math.Pow(Lw/ave_L,c);
            if (R > 255) R = 255;
            if (R < 1) R = 1;

            return R;
        }
    }
}
