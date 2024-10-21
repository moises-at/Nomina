/*desarrollar un programa que permita cargar en un archivo binario la informacion correspondiente de  la n�mina de una empresa y luego consultarla.

Para cada uno de los empleados se tienen los siguientes datos:
    Nombre del empleado.
    Salario b�sico por hora.
    Horas ordinarias trabajadas.
    Horas extras diurnas trabajadas.
    Horas extras nocturnas trabajadas.
    Horas extras dominicales trabajadas

Teniendo en cuenta que las horas extras tienen los siguientes recargos:
    Horas extras diurnas: 25%.
    Horas extras nocturnas: 50%.
    Horas extras dominicales: 75%.
Y que el 10% de retenci�n en la fuente se aplica a las horas extras trabajadas, solo si el valor devengado por este concepto es superior a $200.000.

Se debe implementar un programa con las siguientes opciones 
NOMINA 
1. Cargar datos nomina
2. Generar n�mina
3. Consultar un empleado  (pedir el id y mostrar Salario b�sico por hora, horas ordinarias, horas extras diurnas, nocturnas y dominicales, retenci�n en la fuente,  salario b�sico, salario extras, salario neto  
4. Reporte de n�mina (mostrar id, nombre, total horas extras, salario extras, retenci�n en la fuente salario neto*/

#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
#include <iomanip>
#include <windows.h>
#define N 1000
using namespace std;
//*******************************************************************
struct datos
{
	long id; 
	char nombre[50]; //Nombre del empleado.
    int sbh; //Salario b�sico por hora.
    int hot; //Horas ordinarias trabajadas.
    int hedi; //Horas extras diurnas trabajadas.
    int heno; //Horas extras nocturnas trabajadas.
    int hedo; //Horas extras dominicales trabajadas	
    long sal_he; //salario extras
    long sal_ho; //salario ordinario
	long rete; //retenci�n en la fuente 
	long sal_neto; //salario neto
}; 

int registro(struct datos nomina[]);
void generar(struct datos nomina[], int x);
void consultar();
void reporte();
int menu();
//*******************************************************************
int main()
{
	int opc, x;
	datos nomina[N];
	do
	{
		
		opc=menu();
		switch(opc)
		{
			case 1: x= registro(nomina); break; //Cargar datos nomina
			case 2: generar(nomina, x);break;//Generar n�mina
			case 3: consultar(); break;//Consultar un empleado
			case 4: reporte(); break;//Reporte de n�mina
			case 5: exit(0);
		}
	}while(opc != 5);
}
/*********************************************************************/
int menu()
{
	int opc;
	setlocale(LC_ALL, "spanish");
	do
	{
		system("cls");
		cout<<"NOMINA "<<endl;
		cout<<"1. Cargar datos nomina"<<endl;
		cout<<"2. Generar n�mina"<<endl;
		cout<<"3. Consultar un empleado"<<endl; 
		cout<<"4. Reporte de n�mina"<<endl;
		cout<<"5. Salir"<<endl;
		cout<<"Seleccione el proceso a realizar: ";
		cin>>opc;	
	}while(opc<1 || opc>5);
	return opc;
}
/**************************************************************/
int registro(struct datos nomina[])
{
	int salir;
	static int x=0;//variable para llevar el indice para almacenar cada uno de los registros en el vector 
	do
	{
		system("cls");
		cout<<"Documento de identificaci�n: ";
		cin>>nomina[x].id;
		cout<<"Nombre: ";
		fflush(stdin); gets(nomina[x].nombre);
		cout<<"Salario b�sico por hora: $"; 
		cin>>nomina[x].sbh;
		cout<<"Horas ordinarias trabajadas: "; 
		cin>>nomina[x].hot;
	    cout<<"Horas extras diurnas trabajadas: ";
	    cin>>nomina[x].hedi;
	    cout<<"Horas extras nocturnas trabajadas: ";
	    cin>>nomina[x].heno;
	    cout<<"Horas extras dominicales trabajadas: ";
	    cin>>nomina[x].hedo;
	    x++;
		cout<<"Desea ingresar los datos de otro empleado 1.Si - 0.NO: ";
		cin>>salir;
	}while(salir == 1);
	
	return x;
}
/*****************************************************************************/
void generar(struct datos nomina[], int M)
{
	ofstream archivo("nomina.txt",ios::out | ios::binary);
	if(archivo.fail())
	{
		cout<<"Error para abrir el archivo nomina para escritura "<<endl; system("pause"); exit(0);
	}
	
	for(int x=0; x<M; x++)
	{
		system("cls");
		cout<<"Calculando sueldo del empleado: " <<nomina[x].nombre <<endl;
		Sleep(1000);
		//calcular el salario por horas extra
		/*Horas extras diurnas: 25%.
	    Horas extras nocturnas: 50%.
	    Horas extras dominicales: 75%.*/
	    nomina[x].sal_he = (nomina[x].hedi * nomina[x].sbh*1.25) + (nomina[x].heno * nomina[x].sbh*1.5) + (nomina[x].hedo * nomina[x].sbh*1.75);
		//10% de retenci�n en la fuente se aplica a las horas extras trabajadas, solo si el valor devengado por este concepto es superior a $200.000.*/
		if(nomina[x].sal_he > 200000)
		{
			nomina[x].rete = nomina[x].sal_he * 0.10;
		}
		else 
		{
			nomina[x].rete =0; 	
		}
		nomina[x].sal_ho = nomina[x].sbh * nomina[x].hot; 
		nomina[x].sal_neto = nomina[x].sal_ho + nomina[x].sal_he - nomina[x].rete;
		//Realizamos escritura de los datos que est�n en el registro en el archivo
		archivo.write(reinterpret_cast<char*>(&nomina[x]), sizeof(datos));	
	}//for
	system("cls");
	cout<<"PROCESO N�MINA REALIZADO SATISFACTORIAMENTE" <<endl;
	system("pause");
	archivo.close();
}
/**********************************************************************/
void consultar()
{
	long wid;
	int sw=0;//validar si se encontr� o no el id del empleado en el archivo
	int salir;
	int x=0;
	datos aux[N]; 
	do
	{
		system("cls");
		cout<<"Ingrese el Id del empleado a consultar: ";
		cin>>wid;
		//abrimos el archivo para lectura y buscar el id ingresado
		ifstream archivo("nomina.txt",ios::in | ios::binary);
		if(archivo.fail())
		{
			cout<<"Error para abrir el archivo nomina para lectura "<<endl; system("pause"); exit(0);
		}
		//hacemos una lectura para ubicarnos en el primer registro
		archivo.read(reinterpret_cast<char*>(&aux[x]), sizeof(datos));
		//recorrer el archivo mientras no sea fin de archivo y buscar registro a registro el id a consultar
		sw=0;
		while(!archivo.eof())
		{
			system("cls");
			if(aux[x].id == wid)
			{
				sw=1;
				cout<<"Empleado: " <<aux[x].nombre<<endl;
				cout<<"Salario b�sico por hora: $"<<aux[x].sbh<<endl;
				cout<<"Horas ordinarias: " <<aux[x].hot <<endl;
				cout<<"Horas extras diurnas: " <<aux[x].hedi <<endl;
				cout<<"Nocturnas: " <<aux[x].heno<<endl;
				cout<<"Dominicales: " <<aux[x].hedo<<endl;
				cout<<"Retenci�n en la fuente: $"<<aux[x].rete<<endl;
				cout<<"Salario b�sico: $" <<aux[x].sal_ho<<endl;
				cout<<"Salario extras: $" <<aux[x].sal_he <<endl;
				cout<<"Salario neto : $" <<aux[x].sal_neto <<endl;
				break;
			} 
			x++;
			archivo.read(reinterpret_cast<char*>(&aux[x]), sizeof(datos));
		}//while
		archivo.close();
		if(sw == 0)
		{
			cout<<"Id de empleado no est� registrado en el archivo" <<endl;
		}
		cout<<"Desea consultar otro enpleado 1.SI - 2.No: "; 
		cin>>salir;
	}while(salir == 1);
}
/***************************************************************************/
void reporte()
{
	int x=0;
	long total_nomina=0;
	datos aux[N];
	//abrimos el archivo para lectura y buscar el id ingresado
		ifstream archivo("nomina.txt",ios::in | ios::binary);
	if(archivo.fail())
	{
		cout<<"Error para abrir el archivo nomina para lectura "<<endl; system("pause"); exit(0);
	}
	system("cls");
	//hacemos una lectura para ubicarnos en el primer registro
	archivo.read(reinterpret_cast<char*>(&aux[x]), sizeof(datos));
	//recorrer el archivo mientras no sea fin de archivo y buscar registro a registro el id a consultar
	cout<<setw(10)<<"ID"<<setw(30)<<"NOMBRE"<<setw(10)<<"TOTAL HE"<<setw(15)<<"SALARIO HE"<<setw(15)<<"RETE FUENTE"<<setw(15)<<"NETO"<<endl;
	while(!archivo.eof())
	{
		cout<<setw(10)<<aux[x].id<<setw(30)<<aux[x].nombre<<setw(10)<<aux[x].hedi+aux[x].hedo+aux[x].heno <<setw(15)<<aux[x].sal_he <<setw(15)<<aux[x].rete<<setw(15)<<aux[x].sal_neto<<endl;
		total_nomina += aux[x].sal_neto;
		x++;
		archivo.read(reinterpret_cast<char*>(&aux[x]), sizeof(datos));
	}
	cout<<"Nomina Total Cancelada: $"<<total_nomina<<endl;
	archivo.close();
	system("pause");
}
