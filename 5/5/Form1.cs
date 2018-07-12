using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Collections;
using System.Windows.Input;
using System.Threading;
namespace _5
{
    public partial class Form1 : Form
    {
        circle A = new circle(100, 100, 20, 2, Color.Beige, 5);
        Bitmap bmp;
        public Form1()
        {
            InitializeComponent();
            bmp = new Bitmap(pictur.Width, pictur.Height);
            pictur.MouseClick += OnPictureBoxClicked;
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        void OnPictureBoxClicked(object sender, MouseEventArgs args)
        {
 
        }
        private void button1_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < 500; i++)

                A.draw(bmp);
                A.shift();
                pictur.Image = bmp;
                pictur.Show();
                Thread.Sleep(2000);
            }
        }
    

    public class circle
    {
        public int X;
        public int Y;
        public int R;
        public int V;
        public Color color;
        public double route;
        

        public circle (int x, int y, int r, int v, Color color_ , double route_)
        {
            X = x;
            Y = y;
            R = r;
            V = v;
            color = color_;
            route = route_;


        }
        public void draw(Bitmap bmp)
        {
            int x = X;
            int y = Y;
            Graphics graph = Graphics.FromImage(bmp);
            SolidBrush brash = new SolidBrush(color);
            Pen pen = new Pen(color, 3);
            graph.FillEllipse(brash, X , Y, R, R);
            if ((X) - (R / 2 + 1) < 0) { route += -3.14 / 2.0; X += 2; }
            if ((X) + (R / 2 + 1) > bmp.Width) { route += 3.14 / 2.0; X -= 2; }
            if ((Y) - (R + 1) < 0) { route += 3.14 / 2.0; Y += 2; }
            if ((Y) + (R * 2 + 1) > bmp.Height) { route += -3.14 / 2.0; Y -= 2; }
            x += Convert.ToInt32(Convert.ToDouble(V) * Math.Cos(route));
            y += Convert.ToInt32(Convert.ToDouble(V) * Math.Sin(route));

            
            //if (Y - R == 0)
            X = x;
            Y = y;
        }
        public void shift()
        {
            
            
           
        }
    }

    public class square
    {
        int x;
        int y;
        int A;

    }
}
