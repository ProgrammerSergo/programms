using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Globalization;
using static System.Net.Mime.MediaTypeNames;

namespace Tic80
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            DateTime dt = new DateTime();
            string nowMonth = CultureInfo.CurrentCulture.DateTimeFormat.GetAbbreviatedMonthName(dt.Month);

            // Для атмосфэрности выводим сведения о ПК и инструкцию
            rtbConsole.Text = "ULTIM809 COMPUTER BY IPEK\n" +
                             $"DEBUG ROM V0.3 - {dt.Day} {nowMonth.ToUpper()} {dt.Year}\n" +
                              "512KB AVAILABLE RAM\n\n" +
                              "CARD: NO NAME\n" +
                              "OFFSETS: F33 R279 D311\n" +
                              "MONITOR READY\n\n" +
                              "Commands:\n" +
                              "- open.c - открыть диск C\n" +
                              "- open.my.{Буква диска}\n" +
                              "- open.users - открыть папку 'Пользователи'\n" +
                              "- hi\n" +
                              "-----------\n\n";
            SelectLastLine();
        }


        private void richTextBox1_KeyDown(object sender, KeyEventArgs e)
        {
            // проверка какая клавиша была нажата
            if (e.KeyCode == Keys.Enter)
            {
                // получаем массив слов, из последней строки richTextBox, разделённых точкой
                // т е из команды open.my.C
                // мы получим массив из 3х слов open, my и C
                string[] lastLine = rtbConsole.Lines[rtbConsole.Lines.Count() - 1].Split('.');

                // проверяем первое слово из массива
                switch (lastLine[0])
                {
                    case "open":
                        // если первое слово = open, то проверяем, есть ли ещё слова в нашем массиве
                        // или пользователь больше ничего не ввёл
                        if (lastLine.Length > 1)
                        {
                            // если слов всё таки больше, то проверяем 2е слово в массиве
                            switch (lastLine[1])
                            {
                                case "c":
                                    // открывает проводник по пути, который прописан во 2м аргументе
                                    Process.Start("explorer.exe", @"C:\");
                                    SelectLastLine();
                                    break;
                                case "my":
                                    // обёртываем эту команду в try catch, если в коде, находящимся в try вызовется ошибка
                                    // то она отловится и выполнится код в catch
                                    try
                                    {
                                        // засовываем во 2й аргумент 3ее слово
                                        // (на практике всё работает даже если его не написать, проводник всё равно откроется)
                                        Process.Start("explorer.exe", $@"{lastLine[2]}:\");
                                        SelectLastLine();
                                    }
                                    catch (Exception ex)
                                    {
                                        // если произошла ошибка, то выводим информацию о ней в консоль
                                        // (у меня ещё ни разу не получилось её вызвать даже специально, если 2й аргумент
                                        // неверный, то просто открывается главная страница проводника)
                                        Print(ex.Message);
                                    }
                                    break;
                                case "users":
                                    Process.Start("explorer.exe", @"C:\Users");
                                    SelectLastLine();
                                    break;
                                default:
                                    PrintEx(lastLine[1]);
                                    break;
                            }
                        }
                        else
                        {
                            // если слово в массиве только одно, то выводим ошибку
                            Print("Отсутствует аргумент!");
                        }
                        break;
                    case "hi":
                        Print("Hello Ipek");
                        break;
                    // если ничего не подходит, то срабатывает default
                    default:
                        PrintEx(lastLine[0]);
                        break;
                }
            }
        }

        // установка курсова на новую строку в конце
        private void SelectLastLine()
        {
            rtbConsole.SelectionStart = rtbConsole.Text.Length;
            
        }

        // вывод текста
        private void Print(string text)
        {
            // .AppendText() добавляет текст к тому, который уже написан, а не заменяет его, как .Text = ""
            rtbConsole.AppendText("\n" + text);
            SelectLastLine();
        }

        // вывод ошибки
        private void PrintEx(string text)
        {
            rtbConsole.AppendText($"\nКоманды {text} не существует!");
            SelectLastLine();
        }
    }
}
