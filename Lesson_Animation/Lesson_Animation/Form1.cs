using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Input;

namespace Lesson_Animation
{
    public partial class Form1 : Form
    {
        Graphics gr;       //объявляем объект - графику, на которой будем рисовать
        Pen p;             //объявляем объект - карандаш, которым будем рисовать контур
        SolidBrush fon;    //объявляем объект - заливки, для заливки соответственно фона
        SolidBrush fig;    //и внутренности рисуемой фигуры
        


        circle A = new circle(100, 100, 20,  Color.Beige, 4);
        square B = new square(200 ,100 , 100);
        List<square> bock= new List<square>();
        List<circle> sq = new List<circle>();

        int rad;          // переменная для храрения радиуса рисуемых кругов
        Random rand;      // объект, для получения случайных чисел

        public Form1()
        {

            InitializeComponent();
            bock.Add(B);
            sq.Add(A);
            pictureBox1.MouseClick += OnPictureBoxClicked;
            printO();
            printE();
            gr = pictureBox1.CreateGraphics();
            p = new Pen(Color.Lime);
            fon = new SolidBrush(Color.Black);
            fig = new SolidBrush(Color.Purple);
            rand = new Random();
            gr.FillRectangle(fon, 0, 0, pictureBox1.Width, pictureBox1.Height); 

        }

        void OnPictureBoxClicked(object sender, MouseEventArgs args)
        {
            if (Obs.SelectedIndex < 0) { MessageBox.Show( "Выберите объект", "ERROR"); return; }
            Point location = args.Location;
            int ind = Obs.SelectedIndex;
            bock[ind].X = location.X;
            bock[ind].Y = location.Y;

            for (int i = 0; i < bock.Count; i++)
            {
                bock[i].draw(gr, fig);
            }

        }
        //опишем функцию, которая будет рисовать круг по координатм его центра
        void DrawCircle(int x, int y)
        {
            int xc, yc;
            xc = x - rad;
            yc = y - rad;
            gr.FillEllipse(fig, xc, yc, rad, rad);

            gr.DrawEllipse(p, xc, yc, rad, rad);

        }

        private void button1_Click(object sender, EventArgs e)
        {
                      
            timer1.Enabled = !timer1.Enabled;  

        }

        // для получения данной функции перейдите к конструктору формы 
        // и сделайте двойнок щелчок по таймеру, добавленному на форму
        private void timer1_Tick(object sender, EventArgs e) 
        {


            gr.FillRectangle(fon, 0, 0, pictureBox1.Width, pictureBox1.Height);

            for (int i = 0; i < sq.Count; i++)
            {
                sq[i].draw(gr, fig);
                sq[i].shift(pictureBox1.Width, pictureBox1.Height, rand, bock, sq, i);
            }
            for (int i = 0; i < bock.Count; i++)
            {
                bock[i].draw(gr, fig);
            }
            

        
        }

        private void end_obs_Click(object sender, EventArgs e)
        {
            
            bock.Add(new square(Convert.ToInt32(Ox.Text), Convert.ToInt32(Oy.Text), Convert.ToInt32(Oa.Text)));
            printO();


        }

        private void printE()
        {
            elements.Items.Clear();
            for (int i = 0; i < sq.Count; i++)
            {
                elements.Items.Add(sq[i].ToString());
            }
        }

        private void printO ()
        {
            Obs.Items.Clear();
            for (int i = 0; i < bock.Count; i++)
            {
                Obs.Items.Add(bock[i].ToString());
            }
        }
        private void remObs_Click(object sender, EventArgs e)
        {
            if (Obs.SelectedIndex < 0) { MessageBox.Show("Выберите объект", "ERROR"); return; }

                bock.RemoveAt(Obs.SelectedIndex);
                printO();

        }

        private void button3_Click(object sender, EventArgs e)
        {
            elements.Items.Clear();
            sq.Add(new circle(Convert.ToInt32(Xe.Text), Convert.ToInt32(Ye.Text), Convert.ToInt32(Re.Text), Color.Aqua, Convert.ToDouble(Rote.Text)));
            printE();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (elements.SelectedIndex < 0) { MessageBox.Show("Выберите объект", "ERROR"); return; }

            sq.RemoveAt(elements.SelectedIndex);
            printE();
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void button4_Click(object sender, EventArgs e)
        {
            timer1.Interval = Convert.ToInt32(interva_.Text);
        }
    }





    public class circle
    {
        public int X;
        public int Y;
        public int R;
        public int V = 20;
        public Color color;
        public double route;
        public circle(int x, int y, int r,  Color color_, double route_)
        {
            X = x;
            Y = y;
            R = r;
            color = color_;
            route = route_;
        }

        public string  ToString ()
        {
            return "x = " + X.ToString() + "y = " + Y.ToString() + "r = " + R.ToString(); 
        }
        public void draw( Graphics gr, SolidBrush fig)
        {
            int xc, yc;
            xc =X;
            yc =Y;
            gr.FillEllipse(fig, xc, yc, R, R);
            //gr.DrawEllipse(p, xc, yc, rad, rad);
        }
        public void shift(int X_MAX, int Y_MAX, Random Rand, List<square> L, List<circle> P, int I)
        {
            
            if (X <= 0)
            {
                route = 3.14 - route;
                X += (V); 
            }
            if ((Y) <= 0)
            {
                route = 6.28 - route;
                Y +=  V;
            }

            if (X + R >= X_MAX)
            {
                route = 3.14 - route;
                X -= V;
            }
           
            if (Y + R >= Y_MAX)
            {
                route = 6.28 - route;
                Y -= V ;
            }

            for (int i = 0; i < L.Count; i++)
            {
                if (  X > L[i].X  -R/2
                    & X < L[i].X - R / 2 + V * 2
                    & Y > L[i].Y
                    & Y < L[i].Y + L[i].A)
                {
                    route = 3.14 - route;
                    X -= V;
                }

                if (Y > L[i].Y - R / 2
                    & Y < L[i].Y - R / 2 + V * 2
                    & X > L[i].X
                    & X < L[i].X + L[i].A)
                {
                    route = 6.28 - route;
                    Y -= V;
                }

                if (
                    Y < L[i].Y + L[i].A + R/2
                    & Y > L[i].Y + L[i].A + R /2  - V * 2
                    & X > L[i].X 
                    & X < L[i].X + L[i].A )
                {
                    route = 6.28 - route;
                    Y += V;
                }

                if (
                    X  < L[i].X + L[i].A
                    & X > L[i].X + L[i].A - V*2 
                    & Y > L[i].Y 
                    & Y  < L[i].Y + L[i].A )
                {
                    route = 3.14 - route;
                    X += V;
                }

            }

            
            for (int i = 0; i < P.Count; i++)
            {
                
                 if (
                    X  > P[i].X 
                    & X < P[i].X + 2*P[i].R  
                    & Y > P[i].Y
                    & Y < P[i].Y + 2 * P[i].R
                    & I!=i
                )
                    {
                        route = Rand.NextDouble() * 6.28;
                        P[i].route = Rand.NextDouble() * 6.28;
                    }

            }
            X += Convert.ToInt32(Convert.ToDouble(V) * Math.Cos(route));
            Y += Convert.ToInt32(Convert.ToDouble(V) * Math.Sin(route));

        }
    }

    public class square
    {
        public int X;
        public int Y;
        public int A;
        public square(int x, int y, int a)
        {
            X = x;
            Y = y;
            A = a;

        }
        public string ToString ()
        {
            return "x = " + X.ToString() + "y = " + Y.ToString() + "a = " + A.ToString(); 
        }
        public void draw(Graphics gr, SolidBrush fig)
        {
            gr.FillRectangle(fig, X, Y, A, A);
        }


    }
}
