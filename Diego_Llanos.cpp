struct Cliente {
	int cod_cl;
	string nom_cl;
	string ape_cl;
	string dni_cl;
	string tel_cl;
};

struct nodoArbol1 {
	Cliente *info;
	nodoArbol1 *izq;
	nodoArbol1 *der;
};
Cliente *crearCliente(int cod, string nom, string ape, string dni, string tel) {
	Cliente *c = (Cliente *)malloc(sizeof(Cliente));
	c->cod_cl = cod;
	c->nom_cl = nom;
	c->ape_cl = ape;
	c->dni_cl = dni;
	c->tel_cl = tel;

	return c;
}
nodoArbol1 *crearArbol(Cliente *c, nodoArbol1 *i, nodoArbol1 *d) {
	nodoArbol1 *a = (nodoArbol1 *)malloc(sizeof(nodoArbol1));
	a->info = c;
	a->izq = i;
	a->der = d;

	return a;
}
nodoArbol1 *insertarCliente(nodoArbol1 *nodo, Cliente *c) {
	if (nodo == NULL) {
		return crearArbol(c, NULL, NULL);
	}
	if (c->cod_cl <= nodo->info->cod_cl) {
		nodo->izq = insertarCliente(nodo->izq, c);
	} else {
		nodo->der = insertarCliente(nodo->der, c);
	}
	return nodo;
}
void Agregar_Clientes() {
	string arr[5];
	ListaEn q;
	Cliente *cli;
	int op = 0;
	q = Lista1;
	while (q != NULL) {
		while (op != 5) {
			arr[op] = q->dato;
			q = q->next;
			op++;
		}
		op = 0;
		int num = std::stoi(arr[0]);

		cli = crearCliente(num, arr[1], arr[2], arr[3], arr[4]);
		Arbol_Cliente = insertarCliente(Arbol_Cliente, cli);
	}
}
void mostrarCliente(Cliente *t) {
	if (t != NULL) {
		cout << "--------------------------" << endl;
		cout << "Codigo: " << t->cod_cl << endl;
		cout << "Nombre: " << t->nom_cl << endl;
		cout << "Apellido: " << t->ape_cl << endl;
		cout << "DNI: " << t->dni_cl << endl;
		cout << "Telefono: " << t->tel_cl << endl;
		cout << "--------------------------";
	}
}
void mostrarArbol(nodoArbol1 *a) {
	if (a != NULL) {
		mostrarCliente(a->info);
		mostrarArbol(a->izq);
		mostrarArbol(a->der);
	}
}
Cliente *buscar_c(nodoArbol1 *a, int s) {
	if (a == NULL) {
		cout << "No existe el cliente" << endl;
		return NULL;
	} else if (a->info->cod_cl > s)
		return (buscar_c(a->izq, s));
	else if (a->info->cod_cl < s)
		return (buscar_c(a->der, s));
	else
		return a->info;
}
nodoArbol1 *retirarCliente(nodoArbol1 *a, Cliente *c) {
	nodoArbol1 *t, *f;
	if (a == NULL)
		return NULL;
	else if (a->info->cod_cl > c->cod_cl)
		a->izq = retirarCliente(a->izq, c);
	else if (a->info->cod_cl < c->cod_cl)
		a->der = retirarCliente(a->der, c);
	else {
		if (a->izq == NULL && a->der == NULL) {
			free(a);
			a = NULL;
		} else if (a->izq == NULL) {
			t = a;
			a = a->der;
			free(t);
		} else if (a->der == NULL) {
			t = a;
			a = a->izq;
			free(t);
		} else {
			f = a->izq;
			while (f->der != NULL) {
				f = f->der;
			}
			a->info = f->info;
			f->info = c;
			a->izq = retirarCliente(a->izq, c);
		}
	}
	return a;
}
void eliminarCliente(nodoArbol1 *a) {
	Cliente *cliente;
	int valor, op = 0;
	cout << "Digite el codigo que desea eliminar: ";
	cin >> valor;
	cliente = buscar_c(a, valor);
	retirarCliente(a, cliente);
	cout << "\nCliente Eliminado\n" << endl;
	// EliminarInfoCliente(cliente);
}
void Buscar_Cliente(nodoArbol1 *a) {
	int valor, op = 0;
	Cliente *cliente;
	while (op != 1) {
		cout << "*****Digite el codigo que desea buscar:******";
		cout << "\n Nota:||[1] SALIR" << endl;
		cin >> valor;
		cliente = buscar_c(a, valor);
		if (cliente == NULL) {
			op = 1;
		} else {
			mostrarCliente(cliente);
			cout << "|| [2] Salir" << endl;
			cout << "|| Digite una opcion : \t " << endl;
			cin >> op;
			switch (op) {
			case 1:

				break;
			case 2:
				op = 1;
				break;
			}
		}
	}
}
void menuCliente() {
	int opcion = 0;
	do {
		cout << "*------------------------------*" << endl;
		cout << "\tMenu Clientes" << endl;
		cout << "*------------------------------*" << endl;
		cout << "1.Listar Cliente" << endl;
		cout << "2.Buscar Cliente" << endl;
		cout << "3.Eliminar Cliente" << endl;
		cout << "4.Volver al menu principal" << endl;
		cout << "Digite una opción: ";
		cin >> opcion;
		switch (opcion) {
		case 1:
			listarCliente(Arbol_Cliente);
			break;
		case 2:
			Buscar_Cliente(Arbol_Cliente);
			break;
		case 3:
			eliminarCliente(Arbol_Cliente);
			break;
		case 4:
			opcion = 4;
			break;
		}
	} while (opcion != 4);
}
