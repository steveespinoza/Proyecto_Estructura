

struct ventas {
	int cod;
	string nom_cli;
	string nom_pro;
	int cantidad;
	float precioUnit;
	float precioTotal;
};
typedef struct ventas Ventas;

////////////////////////////////////////////////////////////////////////
ListaEn Lista = NULL, Lista1 = NULL;
nodoArbol1 *Arbol_Cliente = NULL;
NodoArbol3 *Arbol_Venta = NULL;
NodoArbol *Arbol_Insumo = NULL;
/////////////////////////////////////////////////////////////////////////
void insertarInicio(ListaEn &lista, string valor) {
	ListaEn lista1;
	lista1 = new (struct nodo);
	lista1->dato = valor;
	lista1->next = lista;
	lista = lista1;
}

void insertarFinal(ListaEn &lista, string valor) {
	ListaEn t, q = new (struct nodo);

	q->dato = valor;
	q->next = NULL;

	if (lista == NULL) {
		lista = q;
	} else {
		t = lista;
		while (t->next != NULL) {
			t = t->next;
		}
		t->next = q;
	}
}

int insertarAntesDespues() {
	int op, band;
	cout << endl;
	cout << "\t 1. Antes de la posicion           " << endl;
	cout << "\t 2. Despues de la posicion         " << endl;

	cout << "\n\t Opcion : ";
	cin >> op;

	if (op == 1)
		band = -1;
	else
		band = 0;

	return band;
}

void insertarElemento(ListaEn &lista, string valor, int pos) {
	ListaEn q, t;
	int i;
	q = new (struct nodo);
	q->dato = valor;

	if (pos == 1) {
		q->next = lista;
		lista = q;
	} else {
		int x = insertarAntesDespues();
		t = lista;

		for (i = 1; t != NULL; i++) {
			if (i == pos + x) {
				q->next = t->next;
				t->next = q;
				return;
			}
			t = t->next;
		}
	}
	cout << "   Error...Posicion no encontrada..!" << endl;
}

string buscarElemento(ListaEn lista, string valor) {
	ListaEn q = lista;
	int i = 1, busc = 0;

	while (q != NULL) {
		if (q->dato == valor) {
			// cout<<endl<<" Encontrada en posicion "<< i <<endl;
			busc = 1;
			return q->dato;
		}
		q = q->next;
		i++;
	}

	if (busc == 0) {
		cout << "\n\n Codigo no encontrado..!" << endl;
		return "XXXX";
	}
}

string buscarElementoNombre(ListaEn lista, string valor) {
	ListaEn q = lista;
	int busc = 0;

	while (q != NULL) {
		if (q->dato == valor) {
			busc = 1;
			q = q->next;
			return q->dato;
		}
		q = q->next;
	}
}

string buscarElementoPrecio(ListaEn lista, string valor) {
	ListaEn q = lista;
	int busc = 0, i = 1;

	while (q != NULL) {
		if (q->dato == valor) {
			while (i < 5) {
				q = q->next;
				i++;
			}

			return q->dato;
		}
		q = q->next;
	}
}

void ImprimirLista(ListaEn lista) {
	int i = 0;

	while (lista != NULL) {
		cout << ' ' << i + 1 << ") " << lista->dato << endl;
		lista = lista->next;
		i++;
	}
}

void eliminarElemento(ListaEn &lista, string valor) {
	ListaEn p, ant;
	p = lista;

	if (lista != NULL) {
		while (p != NULL) {
			if (p->dato == valor) {
				if (p == lista)
					lista = lista->next;
				else
					ant->next = p->next;

				delete (p);
				return;
			}
			ant = p;
			p = p->next;
		}
	} else
		cout << " Lista vacia..!";
}

//////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

void Agregar_Productos() {
	string arr[7];
	ListaEn q, q1;
	Insumo *insu;
	int op = 0, ver = 0;
	q = Lista;
	q1 = Lista;

	while (q != NULL) {
		if (ver >= 350) {
			while (op != 7) {
				arr[op] = q->dato;
				q = q->next;
				op++;
			}
			op = 0;

			float pre = std::stof(arr[4]);
			int num = std::stoi(arr[0]);
			int sto = std::stoi(arr[5]);
			int ext = std::stoi(arr[6]);

			insu = crearInsumo(num, arr[1], arr[2], arr[3], pre, sto, ext);
			Arbol_Insumo = insertarInsumo(Arbol_Insumo, insu);
		} else {
			q = q->next;
			ver++;
		}
	}
	ver = 0;

	while (q1 != NULL) {
		if (ver < 350) {
			while (op != 7) {
				arr[op] = q1->dato;
				q1 = q1->next;
				op++;
			}
			op = 0;

			float pre = std::stof(arr[4]);
			int num = std::stoi(arr[0]);
			int sto = std::stoi(arr[5]);
			int ext = std::stoi(arr[6]);

			insu = crearInsumo(num, arr[1], arr[2], arr[3], pre, sto, ext);
			Arbol_Insumo = insertarInsumo(Arbol_Insumo, insu);
		} else {
			q1 = q1->next;
			ver++;
		}
	}
}




//////////////////////////////////////////////////////////////////
void Listar_Insumo(NodoArbol *nodo) {
	string arr[7];
	int op = 0, ver = 1, ver1 = 1001;
	Insumo *insu;
	cout << "Digite cuanto productos quiere mostrar:" << endl;
	cin >> ver;
	ver = ver + 1000;
	while (ver1 <= ver) {
		insu = buscar(Arbol_Insumo, ver1);
		imprimirInsumo(insu);
		ver1++;
	}
}

void Buscar_Insumo(nodoArbol *ArbolInsumo) {
	int valor, op = 0;
	Insumo *insu;
	while (op != 1) {
		cout << "*****Digite el codigo que desea buscar:******";
		cout << "\n Nota:||[1] SALIR";
		cin >> valor;
		insu = buscar(ArbolInsumo, valor);
		if (insu == NULL) {
			op = 1;
		} else {
			imprimirInsumo(insu);
			cout << "\n\t¿Que desea hacer?" << endl;
			cout << "|| [1] Imprimir Insumos" << endl;
			cout << "|| [2] Salir" << endl;
			cout << "|| Digite una opcion : \t " << endl;
			cin >> op;
			switch (op) {
			case 1:
				AgregarInsumotxt(insu);
				break;
			case 2:
				op = 1;
				break;
			}
		}
	}
}

void eliminarInsumo(NodoArbol *nodo) {
	Insumo *insu;
	int valor, op = 0;
	cout << "Digite el codigo que desea eliminar:";
	cin >> valor;
	insu = buscar(nodo, valor);
	retirarInsumo(nodo, insu);
	cout << "\nProducto Retirado\n" << endl;
	EliminarInfoInsumo(insu);
}

void crearArbol(NodoArbol3 *raiz) {
	raiz = NULL;
	return;
}

NodoArbol3 *crearNodo(Ventas *ventas, NodoArbol3 *izq, NodoArbol3 *der) {
	NodoArbol3 *c = new NodoArbol3();
	c->sell = ventas;
	c->izq = izq;
	c->der = der;
	// cout<<"Hola";
	return c;
}
//////////////////////////////////////////////////////////////
void ImprimirArbol(NodoArbol3 *n) {
	if (n != NULL) {
		imprimirVentas(n->sell);
		ImprimirArbol(n->izq);
		ImprimirArbol(n->der);
	}
}
/////////////////////////////////////////////////////////////
Ventas *Buscar(NodoArbol3 *n, int valor) {
	// Ventas *venta;
	if (n == NULL) {
		cout << "No hay Venta\n";
		return NULL;
	} else if (valor == n->sell->cod)
		return n->sell;
	else if (valor > n->sell->cod)
		return (Buscar(n->der, valor));
	else
		return (Buscar(n->izq, valor));
}
/////////////////////////////////////////////////////////////
NodoArbol3 *Insertar_Venta(NodoArbol3 *nodo, Ventas *venta) {
	if (nodo == NULL) {
		return crearNodo(venta, NULL, NULL);
	}
	if (venta->cod <= nodo->sell->cod) {
		nodo->izq = Insertar_Venta(nodo->izq, venta);
	} else {
		nodo->der = Insertar_Venta(nodo->der, venta);
	}
	return nodo;
}
//////////////////////////////////////////////////////

NodoArbol3 *retirar(NodoArbol3 *nodo, Ventas *v) {
	NodoArbol3 *nodo1, *nodo2;

	if (nodo == NULL)
		return NULL;
	else if (v->cod < nodo->sell->cod)
		nodo->izq = retirar(nodo->izq, v);
	else if (v->cod > nodo->sell->cod)
		nodo->der = retirar(nodo->der, v);

	else {
		if (nodo->izq == NULL && nodo->der == NULL) {
			free(nodo);
			nodo = NULL;
		} else if (nodo->izq == NULL) {
			nodo1 = nodo;
			nodo = nodo->der;
			free(nodo1);
		} else if (nodo->der == NULL) {
			nodo1 = nodo;
			nodo = nodo->der;
			free(nodo1);
		} else {
			nodo2 = nodo->izq;
			while (nodo2->der != NULL) {
				nodo2 = nodo2->der;
			}
			nodo->sell = nodo2->sell;
			nodo2->sell = v;
			nodo->izq = retirar(nodo->izq, v);
		}
	}
	return nodo;
}

/////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
/////////////////////////LEER ARCHIVOS//////////////////////////////
void AlmacenarArchivo(ListaEn &lista, ListaEn &lista1) {
	ifstream archivo("Insumos.csv");
	ifstream archivo1("Clientes.csv");
	string linea, linea1;
	char delimitador = ',';

	getline(archivo, linea);
	getline(archivo1, linea1);

	while (getline(archivo, linea)) {
		stringstream stream(linea); // Convertir la cadena a un stream
		string CODIGO, NOMBRES, CATEGORIAS, IMAGENES, PRECIOS, STOCK,
			EXISTENCIA;

		// Extraer todos los valores de esa fila
		getline(stream, CODIGO, delimitador);
		getline(stream, NOMBRES, delimitador);
		getline(stream, CATEGORIAS, delimitador);
		getline(stream, IMAGENES, delimitador);
		getline(stream, PRECIOS, delimitador);
		getline(stream, STOCK, delimitador);
		getline(stream, EXISTENCIA, delimitador);

		insertarFinal(lista, CODIGO);
		insertarFinal(lista, NOMBRES);
		insertarFinal(lista, CATEGORIAS);
		insertarFinal(lista, IMAGENES);
		insertarFinal(lista, PRECIOS);
		insertarFinal(lista, STOCK);
		insertarFinal(lista, EXISTENCIA);
	}

	while (getline(archivo1, linea1)) {
		stringstream stream(linea1); // Convertir la cadena a un stream
		string codigo, nombre, apellido, dni, telefono;

		// Extraer todos los valores de esa fila
		getline(stream, codigo, delimitador);
		getline(stream, nombre, delimitador);
		getline(stream, apellido, delimitador);
		getline(stream, dni, delimitador);
		getline(stream, telefono, delimitador);

		insertarFinal(lista1, codigo);
		insertarFinal(lista1, nombre);
		insertarFinal(lista1, apellido);
		insertarFinal(lista1, dni);
		insertarFinal(lista1, telefono);
	}
}



////////////////////////////////////////////////////////////////////
//////////////////FUNCIONES DE VENTAS///////////////////////////////
bool ExisteCliente(ListaEn lista, string codcli) {
	string codigo = buscarElemento(lista, codcli);
	if (codigo == codcli) {
		return true;
	} else {
		return false;
	}
}

bool ExisteInsumo(ListaEn lista, string codins) {
	string codigo = buscarElemento(lista, codins);
	if (codigo == codins) {
		return true;
	} else {
		return false;
	}
}

int Stock_Actual(nodoArbol *nodo, int valor) {
	if (nodo == NULL) {
		// cout<<"No hay producto"<<endl;
		return 0;
	} else if (valor == nodo->info->cod_in) {
		return nodo->info->stock;
	} else if (valor > nodo->info->cod_in)
		return (Stock_Actual(nodo->der, valor));
	else
		return (Stock_Actual(nodo->izq, valor));
}

Insumo *cambiarStock(NodoArbol *nodo, int valor, int cant) {
	if (nodo == NULL) {
		// cout<<"No hay producto"<<endl;
		return NULL;
	} else if (valor == nodo->info->cod_in) {
		nodo->info->stock = cant;
		return nodo->info;
	}

	else if (valor > nodo->info->cod_in)
		return (cambiarStock(nodo->der, valor, cant));
	else
		return (cambiarStock(nodo->izq, valor, cant));
}

void AgregarVenta(ListaEn &lista, ListaEn &lista1, Ventas *venta) {
	string codCli;
	string codIns;
	string newinsu;
	string newcli;
	string precio;
	int cant, ver = 0, sto;
	bool existCli, existInsu;
	ListaEn q;

	while (ver != 1) {
		cout << "Digite el codigo del cliente:";
		cin >> codCli;
		cout << "Digite el codigo del insumo:";
		cin >> codIns;

		existCli = ExisteCliente(Lista1, codCli);
		existInsu = ExisteInsumo(Lista, codIns);
		sto = Stock_Actual(Arbol_Insumo, std::stoi(codIns));

		if (existCli == true && existInsu == true) {
			cout << "\n\t******Codigos encontrados satisfactoriamente******"
				 << endl;
			cout
				<< "\n\tDigite la cantidad del producto seleccionado a llevar: "
				<< endl;
			cout << "Stock Actual:" << sto << endl;
			cin >> cant;
			if (cant <= sto) {
				newinsu = buscarElementoNombre(Lista, codIns);
				newcli = buscarElementoNombre(Lista1, codCli);
				precio = buscarElementoPrecio(Lista, codIns);

				float precio1 = std::stof(precio);

				float precioTotal = cant * precio1;
				cout << "\n\tGenerando Codigo..." << endl;
				int num = 4000 + rand() % (5001 - 4000);

				venta = crearVenta(
					num, newcli, newinsu, cant, precio1, precioTotal);
				Arbol_Venta = Insertar_Venta(Arbol_Venta, venta);
				// ImprimirArbol(Arbol_Venta);
				cout << "\n\t..Codigo Generado..." << endl;
				cout << "Codigo de la Venta:" << num << "\n";

				sto = sto - cant;
				cambiarStock(Arbol_Insumo, std::stoi(codIns), sto);
				cout << "¿Desea Continuar? [SI=0]/[NO=1]:";
				cin >> ver;
			} else {
				cout << "Excedente de Stock" << endl;
				cout << "¿Desea Continuar? [SI=0]/[NO=1]:";
				cin >> ver;
			}
		} else {
			cout << "No existe Algun cliente o producto relacionado";
			cout << "\n¿Desea Continuar? [SI=0]/[NO=1]:";
			cin >> ver;
		}
	}
}

void Eliminar_Venta(NodoArbol3 *nodo) {
	Ventas *venta;
	int valor, op = 0;
	cout << "Digite el codigo que desea eliminar:";
	cin >> valor;
	venta = Buscar(nodo, valor);
	retirar(nodo, venta);
	cout << "\nVenta Retirada\n" << endl;
	EliminarInfoVentas(venta, valor);
}

void Buscar_Venta(NodoArbol3 *nodo) {
	int valor, op = 0;
	Ventas *venta;
	while (op != 1) {
		cout << "*****Digite el codigo que desea buscar:******";
		cout << "\n Nota:||[1] SALIR:";
		cin >> valor;
		venta = Buscar(nodo, valor);
		if (venta == NULL) {
			op = 1;
		} else {
			imprimirVentas(venta);
			cout << "\n\t¿Que desea hacer?" << endl;
			cout << "|| [1] Imprimir Ventas" << endl;
			cout << "|| [2] Salir" << endl;
			cout << "|| Digite una opcion : \t " << endl;
			cin >> op;
			switch (op) {
			case 1:
				AgregarVentatxt(venta);
				break;
			case 2:
				op = 1;
				break;
			}
		}
	}
}


void Menu_Venta() {
	Ventas *venta;
	int opc = 0;
	while (opc != 5) {
		cout << "*********************************************" << endl;
		cout << "\t.:.:.:.:.Menu de Ventas.:.:.:.:." << endl;
		cout << "*********************************************" << endl;
		cout << "|| [1] Agregar Ventas" << endl;
		cout << "|| [2] Listar Ventas" << endl;
		cout << "|| [3] Buscar Ventas" << endl;
		cout << "|| [4] Eliminar Ventas" << endl;
		cout << "|| [5] Salir" << endl;
		cout << "|| Digite una opcion : \t " << endl;
		cin >> opc;
		switch (opc) {
		case 1:
			AgregarVenta(Lista, Lista1, venta);
			break;
		case 2:
			ImprimirArbol(Arbol_Venta);
			break;
		case 3:
			Buscar_Venta(Arbol_Venta);
			break;
		case 4:
			Eliminar_Venta(Arbol_Venta);
			break;
		case 5:
			opc = 5;
			break;
		}
	}
}
/////////////////






