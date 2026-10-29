#include "Menu.h"

Menu::Menu(SistemaTicoPack* sistema) {
    this->sistema = sistema;
}

void Menu::limpiarPantalla() const {
    // Limpia la consola y posiciona el cursor arriba a la izquierda sin usar <cstdlib> ni acumular menús anteriores
    cout << "\033[2J\033[1H";
}

void Menu::pausar() const {
    cout << "\n[Presione ENTER para continuar...]";
    cin.ignore(10000, '\n');
    cin.get();
}

void Menu::confirmarAccion(const string& mensaje) const {
    cout << "\n[EXITO] " << mensaje << endl;
    pausar();
}

string Menu::leerTexto(const string& mensaje) const {
    string texto;
    do {
        cout << mensaje;
        cin >> ws;
        getline(cin, texto);
        if (!Validador::textoValido(texto)) {
            cout << "[Error] El campo no puede estar vacio. Intente de nuevo.\n";
        }
    } while (!Validador::textoValido(texto));
    return texto;
}

int Menu::leerEntero(const string& mensaje) const {
    int valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        if (!cin.fail()) {
            cin.ignore(10000, '\n');
            return valor;
        }
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "[Error] Debe ingresar un numero entero valido.\n";
    }
}

double Menu::leerDecimal(const string& mensaje) const {
    double valor;
    while (true) {
        cout << mensaje;
        cin >> valor;
        if (!cin.fail()) {
            cin.ignore(10000, '\n');
            return valor;
        }
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "[Error] Debe ingresar un valor numerico valido.\n";
    }
}

Fecha Menu::leerFecha(const string& mensaje) const {
    while (true) {
        cout << "\n--- " << mensaje << " ---\n";
        int anio = leerEntero("Anio (ej. 2026): ");
        int mes = leerEntero("Mes (1-12): ");
        int dia = leerEntero("Dia (1-31): ");
        int hora = leerEntero("Hora (0-23): ");
        int minuto = leerEntero("Minuto (0-59): ");
        Fecha fecha(dia, mes, anio, hora, minuto);
        if (fecha.esValida()) return fecha;
        cout << "[Error] La fecha u hora ingresada no es valida. Intente de nuevo.\n";
    }
}

CentroDistribucion* Menu::seleccionarCentro() const {
    if (sistema == nullptr || sistema->getCentros().estaVacia()) {
        cout << "[Aviso] No hay centros de distribucion registrados en el sistema.\n";
        pausar();
        return nullptr;
    }
    string codigo = leerTexto("Ingrese el codigo del centro de distribucion: ");
    CentroDistribucion* centro = sistema->buscarCentro(codigo);
    if (centro == nullptr) {
        cout << "[Error] Centro de distribucion no encontrado.\n";
        pausar();
    }
    return centro;
}

Colaborador* Menu::seleccionarColaborador(CentroDistribucion* centro) const {
    if (centro == nullptr || centro->getColaboradores().estaVacia()) {
        cout << "[Aviso] No hay colaboradores registrados en este centro.\n";
        return nullptr;
    }
    string identificacion = leerTexto("Ingrese la identificacion del colaborador responsable: ");
    Nodo<Colaborador>* nodo = centro->getColaboradores().getPrimero();
    while (nodo != nullptr) {
        if (nodo->getDato()->getIdentificacion() == identificacion) return nodo->getDato();
        nodo = nodo->getSiguiente();
    }
    cout << "[Error] Colaborador no encontrado en este centro.\n";
    return nullptr;
}

void Menu::mostrarTitulo() const {
    cout << "==================================================\n";
    cout << "        TICOPACK LOGISTICS - SISTEMA CENTRAL      \n";
    cout << "==================================================\n";
}

void Menu::mostrarOpciones() const {
    cout << " 1. Gestion de Centros de Distribucion\n";
    cout << " 2. Gestion de Clientes\n";
    cout << " 3. Gestion de Colaboradores\n";
    cout << " 4. Bodegas y Matrices de Almacenamiento\n";
    cout << " 5. Paquetes, Almacenamiento y Reubicacion\n";
    cout << " 6. Solicitudes de Envio\n";
    cout << " 7. Gestion de Despachos y Entregas\n";
    cout << " 8. Reportes del Sistema\n";
    cout << " 0. Salir del Sistema\n";
    cout << "==================================================\n";
}

void Menu::menuCentros() {
    int opcion;
    do {
        limpiarPantalla();
        cout << "==================================================\n";
        cout << "          MODULO: CENTROS DE DISTRIBUCION         \n";
        cout << "==================================================\n";
        cout << " 1. Registrar centro\n 2. Buscar centro\n 3. Mostrar todos los centros\n 4. Eliminar centro\n 0. Regresar al menu principal\n";
        cout << "==================================================\n";
        opcion = leerEntero("Seleccione una opcion: ");

        if (opcion == 1) {
            string codigo = leerTexto("Codigo unico: ");
            if (sistema->buscarCentro(codigo) != nullptr) {
                cout << "[Error] Ya existe un centro con ese codigo.\n";
                pausar();
                continue;
            }
            CentroDistribucion* centro = new CentroDistribucion(codigo,
                leerTexto("Nombre: "), leerTexto("Provincia: "),
                leerTexto("Direccion descriptiva: "), leerTexto("Telefono: "));
            if (!sistema->agregarCentro(centro)) {
                delete centro;
                cout << "[Error] No se pudo registrar el centro.\n";
            }
            else {
                confirmarAccion("Centro registrado correctamente.");
            }
        }
        else if (opcion == 2) {
            CentroDistribucion* c = seleccionarCentro();
            if (c != nullptr) { c->mostrar(); pausar(); }
        }
        else if (opcion == 3) {
            sistema->mostrarEstado();
            pausar();
        }
        else if (opcion == 4) {
            string codigo = leerTexto("Codigo del centro a eliminar: ");
            bool eliminado = sistema->eliminarCentro(codigo);
            if (eliminado) confirmarAccion("Centro eliminado exitosamente.");
            else { cout << "[Error] No se puede eliminar el centro (verifique dependencias).\n"; pausar(); }
        }
    } while (opcion != 0);
}

void Menu::menuClientes() {
    CentroDistribucion* centro = seleccionarCentro();
    if (centro == nullptr) return;
    int opcion;
    do {
        limpiarPantalla();
        cout << "==================================================\n";
        cout << "          MODULO: CLIENTES (Centro: " << centro->getCodigo() << ") \n";
        cout << "==================================================\n";
        cout << " 1. Registrar Persona Fisica\n 2. Registrar Empresa\n 3. Buscar cliente\n 4. Mostrar lista de clientes\n 5. Eliminar cliente\n 0. Regresar\n";
        cout << "==================================================\n";
        opcion = leerEntero("Seleccione una opcion: ");

        if (opcion == 1 || opcion == 2) {
            string id = leerTexto("Identificacion unica: ");
            if (centro->buscarCliente(id) != nullptr) {
                cout << "[Error] Ya existe un cliente con esta identificacion en el centro.\n";
                pausar();
                continue;
            }
            string nombre = leerTexto("Nombre completo o razon social: ");
            string telefono = leerTexto("Telefono: ");
            string correo = leerTexto("Correo electronico: ");
            if (!Validador::correoValido(correo)) {
                cout << "[Error] Formato de correo electronico invalido.\n";
                pausar();
                continue;
            }
            Cliente* cliente = nullptr;
            if (opcion == 1) {
                cliente = new PersonaFisica(id, nombre, telefono, correo);
            }
            else {
                string actividad = leerTexto("Actividad economica: ");
                double descuento = leerDecimal("Porcentaje de descuento autorizado (0 - 100): ");
                if (!Empresa::esPorcentajeValido(descuento)) {
                    cout << "[Error] El descuento debe estar entre 0 y 100.\n";
                    pausar();
                    continue;
                }
                cliente = new Empresa(id, nombre, telefono, correo, actividad, descuento);
            }
            if (!centro->agregarCliente(cliente)) {
                delete cliente;
                cout << "[Error] No se pudo agregar el cliente.\n";
            }
            else {
                confirmarAccion("Cliente registrado exitosamente.");
            }
        }
        else if (opcion == 3) {
            string id = leerTexto("Identificacion a buscar: ");
            Cliente* c = centro->buscarCliente(id);
            if (c != nullptr) { c->mostrar(); }
            else { cout << "[Aviso] Cliente no encontrado.\n"; }
            pausar();
        }
        else if (opcion == 4) {
            cout << "\n--- LISTA DE CLIENTES REGISTRADOS ---\n";
            Nodo<Cliente>* n = centro->getClientes().getPrimero();
            if (n == nullptr) cout << "No hay clientes registrados.\n";
            while (n != nullptr) { n->getDato()->mostrar(); cout << "-----------------------------------\n"; n = n->getSiguiente(); }
            pausar();
        }
        else if (opcion == 5) {
            string id = leerTexto("Identificacion del cliente a eliminar: ");
            bool eliminado = centro->eliminarCliente(id);
            if (eliminado) confirmarAccion("Cliente eliminado correctamente.");
            else { cout << "[Error] No se puede eliminar el cliente (puede tener paquetes o solicitudes asociadas).\n"; pausar(); }
        }
    } while (opcion != 0);
}

void Menu::menuColaboradores() {
    CentroDistribucion* centro = seleccionarCentro();
    if (centro == nullptr) return;
    int opcion;
    do {
        limpiarPantalla();
        cout << "==================================================\n";
        cout << "        MODULO: COLABORADORES (Centro: " << centro->getCodigo() << ")\n";
        cout << "==================================================\n";
        cout << " 1. Registrar colaborador\n 2. Buscar colaborador\n 3. Mostrar colaboradores\n 4. Eliminar colaborador\n 0. Regresar\n";
        cout << "==================================================\n";
        opcion = leerEntero("Seleccione una opcion: ");

        if (opcion == 1) {
            string id = leerTexto("Identificacion: ");
            if (centro->buscarColaborador(id) != nullptr) {
                cout << "[Error] Ya existe un colaborador con esa identificacion.\n";
                pausar();
                continue;
            }
            string nombre = leerTexto("Nombre completo: ");
            Fecha ingreso = leerFecha("Fecha de ingreso");
            string puesto = leerTexto("Puesto: ");
            Colaborador* c = new Colaborador(id, nombre, ingreso, puesto);
            if (!centro->agregarColaborador(c)) {
                delete c;
                cout << "[Error] No se pudo registrar el colaborador.\n";
            }
            else {
                confirmarAccion("Colaborador registrado exitosamente.");
            }
        }
        else if (opcion == 2) {
            Colaborador* c = seleccionarColaborador(centro);
            if (c != nullptr) { c->mostrar(); pausar(); }
        }
        else if (opcion == 3) {
            cout << "\n--- LISTA DE COLABORADORES ---\n";
            Nodo<Colaborador>* n = centro->getColaboradores().getPrimero();
            if (n == nullptr) cout << "No hay colaboradores registrados.\n";
            while (n != nullptr) { n->getDato()->mostrar(); cout << "-----------------------------------\n"; n = n->getSiguiente(); }
            pausar();
        }
        else if (opcion == 4) {
            string id = leerTexto("Identificacion del colaborador a eliminar: ");
            bool eliminado = centro->eliminarColaborador(id);
            if (eliminado) confirmarAccion("Colaborador eliminado.");
            else { cout << "[Error] No se puede eliminar (el colaborador tiene registros activos o bitácoras asociadas).\n"; pausar(); }
        }
    } while (opcion != 0);
}

void Menu::menuBodegas() {
    CentroDistribucion* centro = seleccionarCentro();
    if (centro == nullptr) return;
    int opcion;
    do {
        limpiarPantalla();
        cout << "==================================================\n";
        cout << "          MODULO: BODEGAS Y MATRICES              \n";
        cout << "==================================================\n";
        cout << " 1. Registrar bodega\n 2. Buscar bodega\n 3. Consultar matriz grafica\n 4. Eliminar bodega\n 0. Regresar\n";
        cout << "==================================================\n";
        opcion = leerEntero("Seleccione una opcion: ");

        if (opcion == 1) {
            string codigo = leerTexto("Codigo de bodega (unico en el centro): ");
            if (centro->buscarBodega(codigo) != nullptr) {
                cout << "[Error] Ya existe una bodega con ese codigo en este centro.\n";
                pausar();
                continue;
            }
            string nombre = leerTexto("Nombre de la bodega: ");
            int tipo = leerEntero("Tipo de bodega (1: General, 2: Fragil, 3: Tecnologia, 4: Documentos): ");
            int filas = leerEntero("Cantidad de filas (>0): ");
            int columnas = leerEntero("Cantidad de columnas (>0): ");

            if (!TipoBodega::esValido(tipo) || !Bodega::esDistribucionValida(filas, columnas)) {
                cout << "[Error] Tipo de bodega o dimensiones invalidas.\n";
                pausar();
                continue;
            }
            Bodega* b = new Bodega(codigo, nombre, tipo, filas, columnas);
            if (!centro->agregarBodega(b)) {
                delete b;
                cout << "[Error] No se pudo registrar la bodega.\n";
            }
            else {
                confirmarAccion("Bodega registrada y matriz creada exitosamente.");
            }
        }
        else if (opcion == 2) {
            Bodega* b = centro->buscarBodega(leerTexto("Codigo de bodega: "));
            if (b != nullptr) { b->mostrarDatos(); }
            else { cout << "[Aviso] Bodega no encontrada.\n"; }
            pausar();
        }
        else if (opcion == 3) {
            Bodega* b = centro->buscarBodega(leerTexto("Codigo de bodega: "));
            if (b != nullptr) { b->mostrarMatriz(true); }
            else { cout << "[Aviso] Bodega no encontrada.\n"; }
            pausar();
        }
        else if (opcion == 4) {
            string codigo = leerTexto("Codigo de bodega a eliminar: ");
            bool eliminado = centro->eliminarBodega(codigo);
            if (eliminado) confirmarAccion("Bodega eliminada correctamente.");
            else { cout << "[Error] No se puede eliminar (verifique que todas las celdas estén libres y sin paquetes asignados).\n"; pausar(); }
        }
    } while (opcion != 0);
}

void Menu::menuPaquetes() {
    CentroDistribucion* centro = seleccionarCentro();
    if (centro == nullptr) return;
    int opcion;
    do {
        limpiarPantalla();
        cout << "==================================================\n";
        cout << "          MODULO: GESTION DE PAQUETES             \n";
        cout << "==================================================\n";
        cout << " 1. Registrar paquete\n 2. Buscar paquete\n 3. Almacenar paquete\n 4. Reubicar paquete\n 5. Mostrar paquetes\n 6. Eliminar paquete\n 0. Regresar\n";
        cout << "==================================================\n";
        opcion = leerEntero("Seleccione una opcion: ");

        if (opcion == 1) {
            string codigo = leerTexto("Codigo unico global del paquete: ");
            if (centro->buscarPaquete(codigo) != nullptr) {
                cout << "[Error] El codigo de paquete ya existe en este centro.\n";
                pausar();
                continue;
            }
            string idCliente = leerTexto("Identificacion del cliente propietario (debe pertenecer al centro): ");
            Cliente* cliente = centro->buscarCliente(idCliente);
            if (cliente == nullptr) {
                cout << "[Error] Cliente no encontrado en este centro.\n";
                pausar();
                continue;
            }
            string descripcion = leerTexto("Descripcion del paquete: ");
            double peso = leerDecimal("Peso en kg (>0): ");
            int categoria = leerEntero("Categoria (1: General, 2: Fragil, 3: Tecnologia, 4: Documentos): ");

            if (!Categoria::esValida(categoria) || peso <= 0 || descripcion.empty()) {
                cout << "[Error] Datos del paquete invalidos (verifique peso y categoria).\n";
                pausar();
                continue;
            }
            Paquete* p = new Paquete(codigo, descripcion, peso, categoria, cliente);
            if (!centro->agregarPaquete(p)) {
                delete p;
                cout << "[Error] No se pudo registrar el paquete.\n";
            }
            else {
                confirmarAccion("Paquete registrado con estado RECIBIDO.");
            }
        }
        else if (opcion == 2) {
            Paquete* p = centro->buscarPaquete(leerTexto("Codigo del paquete: "));
            if (p != nullptr) { p->mostrar(); }
            else { cout << "[Aviso] Paquete no encontrado.\n"; }
            pausar();
        }
        else if (opcion == 3) {
            Paquete* p = centro->buscarPaquete(leerTexto("Codigo del paquete a almacenar: "));
            Bodega* b = centro->buscarBodega(leerTexto("Codigo de bodega compatible: "));
            Colaborador* c = seleccionarColaborador(centro);
            if (p != nullptr && b != nullptr && c != nullptr) {
                bool almacenado = centro->almacenarPaquete(p, b, c, leerFecha("Fecha de almacenamiento"));
                if (almacenado) confirmarAccion("Paquete almacenado correctamente en celda asignada.");
                else { cout << "[Error] No se pudo almacenar (verifique compatibilidad de categoría o espacio disponible).\n"; pausar(); }
            }
            else { pausar(); }
        }
        else if (opcion == 4) {
            Paquete* p = centro->buscarPaquete(leerTexto("Codigo del paquete a reubicar: "));
            Bodega* b = centro->buscarBodega(leerTexto("Codigo de bodega destino: "));
            int fila = leerEntero("Fila destino: ");
            int col = leerEntero("Columna destino: ");
            if (p != nullptr && b != nullptr) {
                bool reubicado = centro->reubicarPaquete(p, b, fila, col);
                if (reubicado) confirmarAccion("Paquete reubicado exitosamente.");
                else { cout << "[Error] No se pudo reubicar (celda ocupada, incompatible o inexistente).\n"; pausar(); }
            }
        }
        else if (opcion == 5) {
            cout << "\n--- LISTA DE PAQUETES DEL CENTRO ---\n";
            Nodo<Paquete>* n = centro->getPaquetes().getPrimero();
            if (n == nullptr) cout << "No hay paquetes registrados.\n";
            while (n != nullptr) { n->getDato()->mostrar(); cout << "-----------------------------------\n"; n = n->getSiguiente(); }
            pausar();
        }
        else if (opcion == 6) {
            string codigo = leerTexto("Codigo del paquete a eliminar: ");
            bool eliminado = centro->eliminarPaquete(codigo);
            if (eliminado) confirmarAccion("Paquete eliminado.");
            else { cout << "[Error] No se puede eliminar (solo paquetes en Recibido sin celda, solicitudes o despachos).\n"; pausar(); }
        }
    } while (opcion != 0);
}

void Menu::menuSolicitudes() {
    CentroDistribucion* centro = seleccionarCentro();
    if (centro == nullptr) return;
    int opcion;
    do {
        limpiarPantalla();
        cout << "==================================================\n";
        cout << "          MODULO: SOLICITUDES DE ENVIO            \n";
        cout << "==================================================\n";
        cout << " 1. Crear solicitud de envio\n 2. Buscar solicitud\n 3. Aprobar solicitud (Crea despacho)\n 4. Rechazar solicitud\n 5. Anular solicitud\n 0. Regresar\n";
        cout << "==================================================\n";
        opcion = leerEntero("Seleccione una opcion: ");

        if (opcion == 1) {
            Paquete* p = centro->buscarPaquete(leerTexto("Codigo del paquete (debe estar Almacenado): "));
            Colaborador* c = seleccionarColaborador(centro);
            if (p == nullptr || c == nullptr) { pausar(); continue; }
            if (p->getEstado() != EstadoPaquete::ALMACENADO) {
                cout << "[Error] El paquete no se encuentra en estado Almacenado.\n";
                pausar();
                continue;
            }
            Cliente* cliente = p->getPropietario();
            string codigo = leerTexto("Codigo unico de la solicitud: ");
            if (centro->buscarSolicitud(codigo) != nullptr) {
                cout << "[Error] Ya existe una solicitud con ese codigo en este centro.\n";
                pausar();
                continue;
            }
            double tarifaBase = Tarifas::calcular(p->getPeso(), p->getCategoria(), 0);
            double costoFinal = cliente->calcularCostoFinal(tarifaBase);
            string destino = leerTexto("Descripcion del destino de entrega: ");

            SolicitudEnvio* s = new SolicitudEnvio(codigo, cliente, p, c, centro->getCodigo(), destino, 0, leerFecha("Fecha de solicitud"), costoFinal);
            if (!centro->agregarSolicitud(s)) {
                delete s;
                cout << "[Error] No se pudo crear la solicitud (el paquete ya posee una solicitud pendiente).\n";
            }
            else {
                confirmarAccion("Solicitud creada con estado PENDIENTE. Costo estimado calculado.");
            }
        }
        else if (opcion == 2) {
            SolicitudEnvio* s = centro->buscarSolicitud(leerTexto("Codigo de solicitud: "));
            if (s != nullptr) { s->mostrar(); }
            else { cout << "[Aviso] Solicitud no encontrada.\n"; }
            pausar();
        }
        else if (opcion == 3) {
            SolicitudEnvio* s = centro->buscarSolicitud(leerTexto("Codigo de solicitud a aprobar: "));
            if (s != nullptr) {
                bool aprobado = centro->aprobarSolicitud(s, s->getResponsable(), leerFecha("Fecha de aprobacion"));
                if (aprobado) confirmarAccion("Solicitud aprobada con exito. Despacho creado y paquete en transito.");
                else { cout << "[Error] No se pudo aprobar la solicitud.\n"; pausar(); }
            }
        }
        else if (opcion == 4 || opcion == 5) {
            SolicitudEnvio* s = centro->buscarSolicitud(leerTexto("Codigo de solicitud: "));
            if (s != nullptr) {
                int nuevoEstadoInt = (opcion == 4) ? 2 : 3;
                bool cambiado = s->cambiarEstado(nuevoEstadoInt);
                if (cambiado) confirmarAccion("Estado de solicitud actualizado correctamente.");
                else { cout << "[Error] No se pudo cambiar el estado (la solicitud ya no esta pendiente).\n"; pausar(); }
            }
        }
    } while (opcion != 0);
}

void Menu::menuDespachos() {
    CentroDistribucion* centro = seleccionarCentro();
    if (centro == nullptr) return;
    int opcion;
    do {
        limpiarPantalla();
        cout << "==================================================\n";
        cout << "          MODULO: DESPACHOS Y ENTREGAS            \n";
        cout << "==================================================\n";
        cout << " 1. Buscar despacho\n 2. Mostrar todos los despachos\n 3. Finalizar entrega de despacho\n 0. Regresar\n";
        cout << "==================================================\n";
        opcion = leerEntero("Seleccione una opcion: ");

        if (opcion == 1) {
            Despacho* d = centro->buscarDespacho(leerTexto("Codigo de despacho: "));
            if (d != nullptr) { d->mostrar(); }
            else { cout << "[Aviso] Despacho no encontrado.\n"; }
            pausar();
        }
        else if (opcion == 2) {
            cout << "\n--- LISTA DE DESPACHOS DEL CENTRO ---\n";
            Nodo<Despacho>* n = centro->getDespachos().getPrimero();
            if (n == nullptr) cout << "No hay despachos registrados.\n";
            while (n != nullptr) { n->getDato()->mostrar(); cout << "-----------------------------------\n"; n = n->getSiguiente(); }
            pausar();
        }
        else if (opcion == 3) {
            Despacho* d = centro->buscarDespacho(leerTexto("Codigo de despacho a finalizar: "));
            Colaborador* c = seleccionarColaborador(centro);
            if (d != nullptr && c != nullptr) {
                bool finalizado = centro->finalizarDespacho(d, leerFecha("Fecha de finalizacion"), c);
                if (finalizado) confirmarAccion("Entrega finalizada con exito. Paquete ENTREGADO.");
                else { cout << "[Error] No se pudo finalizar (verifique que el despacho este En proceso y el paquete En transito).\n"; pausar(); }
            }
        }
    } while (opcion != 0);
}

void Menu::menuReportes() {
    CentroDistribucion* centro = seleccionarCentro();
    if (centro == nullptr) return;
    limpiarPantalla();
    cout << "==================================================\n";
    cout << "          MODULO: REPORTES DEL SISTEMA            \n";
    cout << "==================================================\n";
    cout << " 1. Historial de un cliente\n";
    cout << " 2. Clientes por cantidad de envios (Ordenado)\n";
    cout << " 3. Bitacora de cambios de estado de un paquete\n";
    cout << " 4. Consulta de despacho de un paquete\n";
    cout << " 5. Ocupacion de bodegas del centro\n";
    cout << " 6. Despachos gestionados por colaborador\n";
    cout << "==================================================\n";
    int opcion = leerEntero("Seleccione el reporte deseado [1-6]: ");

    if (opcion == 1) {
        Cliente* cli = centro->buscarCliente(leerTexto("Identificacion del cliente: "));
        if (cli != nullptr) Reportes::historialCliente(*centro, cli);
        else cout << "[Error] Cliente no encontrado.\n";
    }
    else if (opcion == 2) {
        Reportes::clientesPorEnvios(*centro);
    }
    else if (opcion == 3) {
        Paquete* p = centro->buscarPaquete(leerTexto("Codigo de paquete: "));
        if (p != nullptr) Reportes::bitacoraPaquete(p);
        else cout << "[Error] Paquete no encontrado.\n";
    }
    else if (opcion == 4) {
        Paquete* p = centro->buscarPaquete(leerTexto("Codigo de paquete: "));
        if (p != nullptr) Reportes::despachoDePaquete(*centro, p);
        else cout << "[Error] Paquete no encontrado.\n";
    }
    else if (opcion == 5) {
        Reportes::ocupacionBodegas(*centro);
    }
    else if (opcion == 6) {
        Colaborador* col = seleccionarColaborador(centro);
        if (col != nullptr) Reportes::despachosPorColaborador(*centro, col);
    }
    else {
        cout << "[Error] Opcion de reporte no valida.\n";
    }
    pausar();
}

void Menu::ejecutar() {
    if (sistema == nullptr) return;
    int opcion;
    do {
        limpiarPantalla();
        mostrarTitulo();
        mostrarOpciones();
        opcion = leerEntero("Seleccione una opcion del menu principal: ");

        switch (opcion) {
        case 1: menuCentros(); break;
        case 2: menuClientes(); break;
        case 3: menuColaboradores(); break;
        case 4: menuBodegas(); break;
        case 5: menuPaquetes(); break;
        case 6: menuSolicitudes(); break;
        case 7: menuDespachos(); break;
        case 8: menuReportes(); break;
        case 0: cout << "\nSaliendo del sistema TicoPack Logistics. ¡Hasta pronto!\n"; break;
        default:
            cout << "[Error] Opcion invalida. Intente de nuevo.\n";
            pausar();
            break;
        }
    } while (opcion != 0);
    limpiarPantalla();
}