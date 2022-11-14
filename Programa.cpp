//Librerias
#include<iostream>
#include<cstring>
#include<fstream>
#include<stdlib.h>
#include<string>
using namespace std;
//Declaracion de funciones
void registrarArticulo(int,int);
int verificarExistencia(int,int);
void traslacionRegistros(int,int);
void listaArticulos(int);
void cargarArchivo(int*,int*);
void generarArchivo(int,int);
//Estructura de datos
struct informacion{
	int numeroArticulo;
	char nombreVideojuego[40];
	int anioLanzamiento;
	char clasificacion[20];
	char caracteristicas[40];
	char descripcion[80];
	char genero[20];
	float precio;
	float impuesto;
	float total;
}videojuego[20];
//Funcion main()
int main(){
	//Declaracion de variables
	int opcion, siguienteId=1, siguienteIndice=0, idBuscar, indiceEncontrado;
	//Verificacion de integridad
	fstream archivo;
	archivo.open("informacion.txt");
	if(archivo)
		//Carga de archivo de informacion
	    cargarArchivo(&siguienteId,&siguienteIndice);
	archivo.close();
	//Ciclo del menu
	do{
		//Impresión del formato
		cout<<"//////////Menu principal//////////\n\n";
		cout<<"1) Agregar articulo\n";
		cout<<"2) Modificar articulo\n";
		cout<<"3) Eliminar articulo\n";
		cout<<"4) Lista de articulos\n";
		cout<<"5) Limpiar pantalla\n";
		cout<<"6) Salir\n\n";
		cout<<"Opcion: ";
		cin>>opcion;
		//Llamada de funciones
		switch(opcion){
			case 1:
				//Se agrega un nuevo articulo
				cout<<"\n//////////Nuevo articulo//////////\n\n";
				registrarArticulo(siguienteId,siguienteIndice);
				cout<<"\n\n//////////Articulo registrado//////////\n\n";
				system("pause");
				cout<<"\n";
				//Se actualizan las variables de control
				siguienteId++;
				siguienteIndice++;
				break;
			case 2:
				//Se pregunta el no. de articulo a modificar
				cout<<"\n//////////Modificar articulo//////////\n\n";
				do{
					cout<<"No. articulo a modificar: ";
					cin>>idBuscar;
					//Se verifica si existe ese no. de articulo
					indiceEncontrado=verificarExistencia(idBuscar,siguienteId);
				}while(indiceEncontrado==-1);
				cout<<"\n";
				//Se sobreescribre el registro seleccionado
				registrarArticulo(idBuscar,indiceEncontrado);
				cout<<"\n\n//////////Articulo actualizado//////////\n\n";
				system("pause");
				cout<<"\n";
				break;
			case 3:
				//Se pregunta el no. de articulo a eliminar
				cout<<"\n//////////Eliminar articulo//////////\n\n";
				do{
					cout<<"No. articulo a eliminar: ";
					cin>>idBuscar;
					//Se verifica si existe ese no. de articulo
					indiceEncontrado=verificarExistencia(idBuscar,siguienteId);
				}while(indiceEncontrado==-1);
				cout<<"\n";
				//Se trasladan los registros sobrescribiendo y borrando el seleccionado
				traslacionRegistros(indiceEncontrado,siguienteId);
				siguienteId--;
				cout<<"\n\n//////////Articulo eliminado//////////\n\n";
				system("pause");
				cout<<"\n";
				break;
			case 4:
				//Se imprime la lista de registros
				listaArticulos(siguienteIndice);
				break;
			case 5:
				//Se limpia la pantalla
				system("cls");
				break;
		}
	}while(opcion!=6);
	//Generacion del archivo de informacion
	generarArchivo(siguienteId,siguienteIndice);
	//Saliendo del programa
	cout<<"\n//////////Saliendo del programa//////////\n\n";
}
//Funcion nuevoArticulo()
void registrarArticulo(int noArticulo, int indice){
	//Asignacion de numero de articulo
	cout<<"No. articulo: "<<noArticulo<<endl;
	videojuego[indice].numeroArticulo=indice+1;
	//Lectura del nombre del videojuego
	cout<<"Nombre del videojuego: ";
	cin.ignore(1);
	cin.getline(videojuego[indice].nombreVideojuego,40);
	//Lectura del año de lanzamiento
	cout<<"Anio de lanzamiento: ";
	cin>>videojuego[indice].anioLanzamiento;
	//Lectura de la clasificacion
	cout<<"Clasificacion: ";
	cin.ignore(1);
	cin.getline(videojuego[indice].clasificacion,20);
	//Lectura de las caracteristicas
	cout<<"Caracteristicas: ";
	cin.getline(videojuego[indice].caracteristicas,40);
	//Lectura de la descripcion
	cout<<"Descripcion: ";
	cin.getline(videojuego[indice].descripcion,80);
	//Lectura del genero
	cout<<"Genero: ";
	cin.getline(videojuego[indice].genero,20);
	//Lectura del precio unitario
	cout<<"Precio unitario: $";
	cin>>videojuego[indice].precio;
	//Calculo del impuesto (16%)
	cout<<"Impuesto: $";
	videojuego[indice].impuesto=videojuego[indice].precio*.16;
	cout<<videojuego[indice].impuesto;
	//Calculo del precio total
	cout<<"\nTotal: $";
	videojuego[indice].total=videojuego[indice].precio*1.16;
	cout<<videojuego[indice].total;
}
//Funcion verificarExistencia
int verificarExistencia(int aBuscar, int siguienteId){
	//Ciclo de verificacion
	for(int contador=0;contador<siguienteId;contador++)
		//Si se encuentra el numero del articulo se regresa un TRUE
		if(videojuego[contador].numeroArticulo==aBuscar)
			return contador;
	//Si no se encuentra el numero del articulo se regresa un FALSE
	return -1;
}
//Funcion traslacionRegistros()
void traslacionRegistros(int inicio, int limite){
	//Ciclo que mueve los valores de toda la estructura en un indice 
	//con todos los registros que hay por delante
	for(int contador=inicio;contador<limite-1;contador++){
		videojuego[contador].numeroArticulo=videojuego[contador+1].numeroArticulo;
		strcpy(videojuego[contador].nombreVideojuego,videojuego[contador+1].nombreVideojuego);
		videojuego[contador].anioLanzamiento=videojuego[contador+1].anioLanzamiento;
		strcpy(videojuego[contador].clasificacion,videojuego[contador+1].clasificacion);
		strcpy(videojuego[contador].caracteristicas,videojuego[contador+1].caracteristicas);
		strcpy(videojuego[contador].descripcion,videojuego[contador+1].descripcion);
		strcpy(videojuego[contador].genero,videojuego[contador+1].genero);
		videojuego[contador].precio=videojuego[contador+1].precio;
		videojuego[contador].impuesto=videojuego[contador+1].impuesto;
		videojuego[contador].total=videojuego[contador+1].total;
	}
}
//Funcion listaArticulos()
void listaArticulos(int indice){
	//Impresion de formato
	cout<<"\n//////////Lista de articulos//////////\n\n";
	cout<<"No.\tNombre\tAnio\tClasif.\tGenero\tTotal\n\n";
	//Ciclo de impresion de datos relevantes
	for(int contador=0;contador<indice;contador++){
		cout<<videojuego[contador].numeroArticulo<<"\t";
		cout<<videojuego[contador].nombreVideojuego<<"\t";
		cout<<videojuego[contador].anioLanzamiento<<"\t";
		cout<<videojuego[contador].clasificacion<<"\t";
		cout<<videojuego[contador].genero<<"\t";
		cout<<videojuego[contador].total<<"\n";		
	}
	cout<<"\n";
	system("pause");
	cout<<"\n";
}
//Funcion cargarArchivo;
void cargarArchivo(int*siguienteId,int*siguienteIndice){
	//Declaracion de flujo de lectura
	ifstream archivo;
	archivo.open("informacion.txt");
	string lineaLeida;
	//Lectura de pametros
	getline(archivo,lineaLeida);
	*siguienteId=stoi(lineaLeida);
	getline(archivo,lineaLeida);
	*siguienteIndice=stoi(lineaLeida);
	    getline(archivo,lineaLeida);
	//Lectura de datos
	for(int contador=0;contador<*siguienteIndice;contador++){
	    getline(archivo,lineaLeida);
	    videojuego[contador].numeroArticulo=stoi(lineaLeida);
	    getline(archivo,lineaLeida);
	    strcpy(videojuego[contador].nombreVideojuego,lineaLeida.c_str());
	    getline(archivo,lineaLeida);
	    videojuego[contador].anioLanzamiento=stoi(lineaLeida);
	    getline(archivo,lineaLeida);
	    strcpy(videojuego[contador].clasificacion,lineaLeida.c_str());
	    getline(archivo,lineaLeida);
	    strcpy(videojuego[contador].caracteristicas,lineaLeida.c_str());
	    getline(archivo,lineaLeida);
	    strcpy(videojuego[contador].descripcion,lineaLeida.c_str());
	    getline(archivo,lineaLeida);
	    strcpy(videojuego[contador].genero,lineaLeida.c_str());
	    getline(archivo,lineaLeida);
	    videojuego[contador].precio=stof(lineaLeida);
	    getline(archivo,lineaLeida);
	    videojuego[contador].impuesto=stof(lineaLeida);
	    getline(archivo,lineaLeida);
	    videojuego[contador].total=stof(lineaLeida);
	    getline(archivo,lineaLeida);
	}
	archivo.close();
}
//Funcion generarArchivo()
void generarArchivo(int siguienteId, int siguienteIndice){
	//Declaracion de flujo de escritura
	ofstream archivo;
	archivo.open("informacion.txt");
	//Escritura de parametros
	archivo<<siguienteId<<"\n"<<siguienteIndice<<"\n\n";
	//Ciclo de impresion de datos
	for(int contador=0;contador<siguienteIndice;contador++){
		archivo<<videojuego[contador].numeroArticulo<<"\n";
		archivo<<videojuego[contador].nombreVideojuego<<"\n";
		archivo<<videojuego[contador].anioLanzamiento<<"\n";
		archivo<<videojuego[contador].clasificacion<<"\n";
		archivo<<videojuego[contador].caracteristicas<<"\n";
		archivo<<videojuego[contador].descripcion<<"\n";
		archivo<<videojuego[contador].genero<<"\n";
		archivo<<videojuego[contador].precio<<"\n";
		archivo<<videojuego[contador].impuesto<<"\n";
		archivo<<videojuego[contador].total<<"\n\n";	
	}
	archivo.close();
	cout<<"\n//////////Reporte impreso//////////\n";
}
