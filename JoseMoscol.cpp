struct insumo 
{
	int cod_in;
	string nom_in;
	string cat_in;
	string imag_in;
	float precio_in;
	int stock;
	int exist;
};
typedef struct insumo Insumo;

struct nodoArbol 
{
	Insumo *info;
	nodoArbol *izq, *der;
};
typedef struct nodoArbol NodoArbol;

//CREAR INSUMO
Insumo *crearInsumo(
	int codIn,
	string nombIn,
	string catIn,
	string imagIn,
	float precioIn,
	int stock,
	int exist) {
	Insumo *i = new Insumo();
	i->cod_in = codIn;
	i->nom_in = nombIn;
	i->cat_in = catIn;
	i->imag_in = imagIn;
	i->precio_in = precioIn;
	i->stock = stock;
	i->exist = exist;
	return i;
}

//IMPRIMIR INSUMO
void imprimirInsumo(Insumo *t) 
{
	if (t != NULL) 
  {
		printf("\n----------------------------------");
		printf("\nCodigo: %i ", t->cod_in);
		cout << "\nNombre: " << t->nom_in;
		cout << "\nDescripcion: " << t->cat_in;
		cout << "\nPresentacion: " << t->imag_in;
		printf("\nPrecio: %.2f ", t->precio_in);
		printf("\nStock: %d ", t->stock);
		printf("\nExistencia: %d ", t->exist);
		printf("\n----------------------------------");
	}
}

NodoArbol *crearArbol(Insumo *t, NodoArbol *i, NodoArbol *d) 
{
	NodoArbol *a = new NodoArbol();
	a->info = t;
	a->izq = i;
	a->der = d;
	return a;
}

// IMPRIMIR ARBOL DE INSUMOS
void imprimirArbol(NodoArbol *n) 
{
	if (n != NULL) {
		imprimirInsumo(n->info);
		imprimirArbol(n->izq);
		imprimirArbol(n->der);
	}
}

// METODO BUSCAR
Insumo *buscar(NodoArbol *a, int s) 
{
	if (a == NULL) {
		cout << "No hay producto" << endl;
		return NULL;
	} else if (a->info->cod_in > s)
		return (buscar(a->izq, s));
	else if (a->info->cod_in < s)
		return (buscar(a->der, s));
	else
		return a->info;
}

// METODO INSERTAR
NodoArbol *insertarInsumo(NodoArbol *nodo, Insumo *t) 
{
	if (nodo == NULL) {
		return crearArbol(t, NULL, NULL);
	}
	if (t->cod_in <= nodo->info->cod_in) {
		nodo->izq = insertarInsumo(nodo->izq, t);
	} else {
		nodo->der = insertarInsumo(nodo->der, t);
	}
	return nodo;
}

// METODO RETIRAR
NodoArbol *retirarInsumo(NodoArbol *r, Insumo *v) 
{
	NodoArbol *t, *f;
	if (r == NULL)
		return NULL;
	else if (r->info->cod_in > v->cod_in)
		r->izq = retirarInsumo(r->izq, v);
	else if (r->info->cod_in < v->cod_in)
		r->der = retirarInsumo(r->der, v);
	else { // encontro el nodo a retirar
		if (r->izq == NULL && r->der == NULL) {
			free(r);
			r = NULL;
		} else if (r->izq == NULL) {
			t = r;
			r = r->der;
			free(t);
		} else if (r->der == NULL) {
			t = r;
			r = r->izq;
			free(t);
		} else {
			f = r->izq;
			while (f->der != NULL) {
				f = f->der;
			}
			r->info = f->info;
			f->info = v;
			r->izq = retirarInsumo(r->izq, v);
		}
	}
	return r;
}
