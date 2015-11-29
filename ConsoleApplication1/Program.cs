using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication1
{
    interface MyInterface
    {
        void DoStuff();
    }
    class MyClass : MyInterface
    {
        public void DoStuff() { }
    }
    class MyClass2 : MyClass
    {
        new public void DoStuff()
        {
            
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            MyInterface i = new MyClass2();
            i.DoStuff();
        }
    }
}
