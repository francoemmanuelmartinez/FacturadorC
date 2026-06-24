#pragma once

// === ControladorLogin ===
void ControladorLogin::botonLogin_Click(Object^ sender, EventArgs^ e) {
    String^ mail = this->vistaLogin->mailTextField->Text;
    String^ password = this->vistaLogin->passwordTextField->Text;
    if (String::IsNullOrEmpty(mail) || String::IsNullOrEmpty(password)) {
        MessageBox::Show(L"Ingrese ambos datos");
        return;
    }
    if (this->validar(mail, password)) {
        this->logear();
    }
    else {
        MessageBox::Show(L"Credenciales incorrectas");
    }
}

void ControladorLogin::botonRegistrar_Click(Object^ sender, EventArgs^ e) {
    gcnew ControladorRegistro(this->ventanaPrincipal);
}

void ControladorLogin::logear() {
    String^ rol = this->usuario->Rol;
    if (rol == L"Administrador") {
        gcnew ControladorAdmin(this->usuario, this->ventanaPrincipal);
    }
    else if (rol == L"Cajero") {
        gcnew ControladorCajero(this->usuario, this->ventanaPrincipal);
    }
    else if (rol == L"Deposito") {
        gcnew ControladorDepositoABM(this->usuario, this->ventanaPrincipal);
    }
    else if (rol == L"Ninguno") {
        MessageBox::Show(L"Su cuenta no tiene un rol asignado. Contacte a un administrador.");
    }
    else {
        MessageBox::Show(L"USUARIO INVALIDO");
    }
}

// === ControladorAdmin ===
void ControladorAdmin::botonUsuarios_Click(Object^ sender, EventArgs^ e) {
    gcnew ControladorUsuarioABM(this->usuario, this->ventanaPrincipal);
}

void ControladorAdmin::botonClientes_Click(Object^ sender, EventArgs^ e) {
    gcnew ControladorClienteABM(this->usuario, this->ventanaPrincipal);
}

void ControladorAdmin::botonFacturar_Click(Object^ sender, EventArgs^ e) {
    gcnew ControladorCajero(this->usuario, this->ventanaPrincipal);
}

void ControladorAdmin::botonDeposito_Click(Object^ sender, EventArgs^ e) {
    gcnew ControladorDepositoABM(this->usuario, this->ventanaPrincipal);
}

void ControladorAdmin::botonProveedores_Click(Object^ sender, EventArgs^ e) {
    gcnew ControladorProveedorABM(this->usuario, this->ventanaPrincipal);
}

void ControladorAdmin::cerrarSesion_Click(Object^ sender, EventArgs^ e) {
    gcnew ControladorLogin(this->ventanaPrincipal);
}

// === ControladorCajero ===
void ControladorCajero::volverButton_Click(Object^ sender, EventArgs^ e) {
    if (this->usuario->Rol == L"Administrador") {
        gcnew ControladorAdmin(this->usuario, this->ventanaPrincipal);
    }
    else {
        gcnew ControladorLogin(this->ventanaPrincipal);
    }
}

void ControladorCajero::buscarClienteButton_Click(Object^ sender, EventArgs^ e) {
    String^ dni = this->vista->textFieldBuscarCliente->Text->Trim();
    if (String::IsNullOrEmpty(dni)) return;
    auto ctrl = gcnew ControladorClienteABM();
    auto cl = ctrl->buscarCliente(dni, 1);
    if (cl != nullptr) {
        this->vista->textFieldIDCliente->Text = cl->Id.ToString();
        this->vista->textFieldNombreCliente->Text = cl->Nombre;
        this->vista->textFieldApellidoCliente->Text = cl->Apellido;
        this->vista->textFieldDNICliente->Text = cl->Dni;
        this->vista->textFieldDomicilioCliente->Text = cl->Direccion;
        this->vista->textFieldTelefonoCliente->Text = cl->Telefono;
        this->vista->textFieldMailCliente->Text = cl->Mail;
    }
}

void ControladorCajero::modificarClienteButton_Click(Object^ sender, EventArgs^ e) {
    String^ idStr = this->vista->textFieldIDCliente->Text->Trim();
    if (String::IsNullOrEmpty(idStr)) {
        MessageBox::Show(L"No hay cliente seleccionado");
        return;
    }
    int id = Int32::Parse(idStr);
    auto valores = VistaFormulario::mostrarDialogo(L"Modificar Cliente",
        gcnew VistaFormulario::Campo(L"Nombre:", this->vista->textFieldNombreCliente->Text, L"Texto", true),
        gcnew VistaFormulario::Campo(L"Apellido:", this->vista->textFieldApellidoCliente->Text, L"Texto", true),
        gcnew VistaFormulario::Campo(L"DNI:", this->vista->textFieldDNICliente->Text, L"Numerico", true),
        gcnew VistaFormulario::Campo(L"Telefono:", this->vista->textFieldTelefonoCliente->Text, L"Numerico"),
        gcnew VistaFormulario::Campo(L"Direccion:", this->vista->textFieldDomicilioCliente->Text, L"Alfanumerico"),
        gcnew VistaFormulario::Campo(L"Mail:", this->vista->textFieldMailCliente->Text, L"Alfanumerico", true)
    );
    if (valores != nullptr) {
        auto confirm = MessageBox::Show(L"?Confirmar modificacion del cliente?", L"Confirmar", MessageBoxButtons::YesNo);
        if (confirm == DialogResult::Yes) {
            auto ctrl = gcnew ControladorClienteABM();
            if (ctrl->modificarCliente(id, valores[L"Nombre:"], valores[L"Apellido:"], valores[L"DNI:"],
                valores[L"Telefono:"], valores[L"Direccion:"], valores[L"Mail:"])) {
                this->vista->textFieldNombreCliente->Text = valores[L"Nombre:"];
                this->vista->textFieldApellidoCliente->Text = valores[L"Apellido:"];
                this->vista->textFieldDNICliente->Text = valores[L"DNI:"];
                this->vista->textFieldDomicilioCliente->Text = valores[L"Direccion:"];
                this->vista->textFieldTelefonoCliente->Text = valores[L"Telefono:"];
                this->vista->textFieldMailCliente->Text = valores[L"Mail:"];
            }
        }
    }
}

void ControladorCajero::nuevoClienteButton_Click(Object^ sender, EventArgs^ e) {
    auto valores = VistaFormulario::mostrarDialogo(L"Nuevo Cliente",
        gcnew VistaFormulario::Campo(L"Nombre:", L"", L"Texto", true),
        gcnew VistaFormulario::Campo(L"Apellido:", L"", L"Texto", true),
        gcnew VistaFormulario::Campo(L"DNI:", L"", L"Numerico", true),
        gcnew VistaFormulario::Campo(L"Telefono:", L"", L"Numerico"),
        gcnew VistaFormulario::Campo(L"Direccion:", L"", L"Alfanumerico"),
        gcnew VistaFormulario::Campo(L"Mail:", L"", L"Alfanumerico", true)
    );
    if (valores != nullptr) {
        auto ctrl = gcnew ControladorClienteABM();
        int id = ctrl->agregarCliente(valores[L"Nombre:"], valores[L"Apellido:"], valores[L"DNI:"],
            valores[L"Telefono:"], valores[L"Direccion:"], valores[L"Mail:"]);
        if (id > -1) {
            this->vista->textFieldIDCliente->Text = id.ToString();
            this->vista->textFieldNombreCliente->Text = valores[L"Nombre:"];
            this->vista->textFieldApellidoCliente->Text = valores[L"Apellido:"];
            this->vista->textFieldDNICliente->Text = valores[L"DNI:"];
            this->vista->textFieldDomicilioCliente->Text = valores[L"Direccion:"];
            this->vista->textFieldTelefonoCliente->Text = valores[L"Telefono:"];
            this->vista->textFieldMailCliente->Text = valores[L"Mail:"];
        }
    }
}

void ControladorCajero::buscarProductoButton_Click(Object^ sender, EventArgs^ e) {
    String^ texto = this->vista->textFieldBuscarProducto->Text->Trim();
    if (String::IsNullOrEmpty(texto)) return;
    auto ctrl = gcnew ControladorDepositoABM();
    auto resultados = ctrl->buscarProducto(texto, 1);
    if (resultados->Count > 0) {
        auto p = resultados[0];
        this->vista->textFieldIDProducto->Text = p->Id.ToString();
        this->vista->textFieldDescripcionProducto->Text = p->Descripcion;
        this->vista->textFieldPrecioProducto->Text = p->Precio.ToString(L"F2");
        this->vista->textFieldStock->Text = p->Stock.ToString();
        this->vista->textFieldProveedorProducto->Text = p->NombreProveedor != nullptr ? p->NombreProveedor : L"";
    }
}

void ControladorCajero::modificarProductoButton_Click(Object^ sender, EventArgs^ e) {
    String^ idStr = this->vista->textFieldIDProducto->Text->Trim();
    if (String::IsNullOrEmpty(idStr)) {
        MessageBox::Show(L"No hay producto seleccionado");
        return;
    }
    int id = Int32::Parse(idStr);
    auto valores = VistaFormulario::mostrarDialogo(L"Modificar Producto",
        gcnew VistaFormulario::Campo(L"Descripcion:", this->vista->textFieldDescripcionProducto->Text, L"Alfanumerico", true),
        gcnew VistaFormulario::Campo(L"Precio:", this->vista->textFieldPrecioProducto->Text, L"Precio", true),
        gcnew VistaFormulario::Campo(L"Stock:", this->vista->textFieldStock->Text, L"Numerico", true)
    );
    if (valores != nullptr) {
        auto confirm = MessageBox::Show(L"?Confirmar modificacion del producto?", L"Confirmar", MessageBoxButtons::YesNo);
        if (confirm == DialogResult::Yes) {
            auto ctrl = gcnew ControladorDepositoABM();
            bool ok = ctrl->modificarProducto(id, valores[L"Descripcion:"],
                Double::Parse(valores[L"Precio:"]), Int32::Parse(valores[L"Stock:"]), 0);
            if (ok) {
                this->vista->textFieldDescripcionProducto->Text = valores[L"Descripcion:"];
                this->vista->textFieldPrecioProducto->Text = valores[L"Precio:"];
                this->vista->textFieldStock->Text = valores[L"Stock:"];
            }
        }
    }
}

void ControladorCajero::nuevoProductoButton_Click(Object^ sender, EventArgs^ e) {
    auto ctrlProv = gcnew ControladorProveedorABM();
    auto proveedores = ctrlProv->obtenerProveedoresPorHabilitado(1);
    auto opciones = gcnew array<String^>(proveedores->Count);
    for (int i = 0; i < proveedores->Count; i++) {
        opciones[i] = proveedores[i]->Id + L" - " + proveedores[i]->Nombre;
    }
    auto valores = VistaFormulario::mostrarDialogo(L"Nuevo Producto",
        gcnew VistaFormulario::Campo(L"Descripcion:", L"", L"Alfanumerico", true),
        gcnew VistaFormulario::Campo(L"Precio:", L"", L"Precio", true),
        gcnew VistaFormulario::Campo(L"Stock:", L"", L"Numerico", true),
        gcnew VistaFormulario::Campo(L"Proveedor:", opciones, true)
    );
    if (valores != nullptr) {
        auto ctrl = gcnew ControladorDepositoABM();
        String^ selProv = valores[L"Proveedor:"];
        int idProveedor = 0;
        if (!String::IsNullOrEmpty(selProv) && selProv->Contains(L" - "))
            idProveedor = Int32::Parse(selProv->Split(gcnew array<String^> { L" - " }, StringSplitOptions::None)[0]);
        int id = ctrl->agregarProducto(valores[L"Descripcion:"],
            Double::Parse(valores[L"Precio:"]), Int32::Parse(valores[L"Stock:"]), idProveedor);
        if (id > -1) {
            this->vista->textFieldIDProducto->Text = id.ToString();
            this->vista->textFieldDescripcionProducto->Text = valores[L"Descripcion:"];
            this->vista->textFieldPrecioProducto->Text = valores[L"Precio:"];
            this->vista->textFieldStock->Text = valores[L"Stock:"];
        }
    }
}

// === ControladorFactura ===
void ControladorFactura::verDetalleButton_Click(Object^ sender, EventArgs^ e) {
    if (this->vistaFactura->tableFacturas->SelectedRows->Count == 0) {
        MessageBox::Show(L"Seleccione una factura");
        return;
    }
    int fila = this->vistaFactura->tableFacturas->SelectedRows[0]->Index;
    int idFactura = safe_cast<int>(this->vistaFactura->tableFacturas->Rows[fila]->Cells[0]->Value);
    auto vdf = gcnew VistaDetallesFactura();
    this->ventanaPrincipal->setVista(vdf->panelDetallesFactura);

    this->cargarFacturaCompleta(vdf, idFactura);
    this->cargarDetalles(vdf->tableDetalles, idFactura);

    vdf->volverButton->Click += gcnew EventHandler(this, &ControladorFactura::volverButtonDetalle_Click);
}

void ControladorFactura::volverButtonDetalle_Click(Object^ sender, EventArgs^ e) {
    gcnew ControladorFactura(this->usuario, this->ventanaPrincipal, this->idCliente, this->nombreCliente, this->apellidoCliente);
}

void ControladorFactura::volverButton_Click(Object^ sender, EventArgs^ e) {
    gcnew ControladorClienteABM(this->usuario, this->ventanaPrincipal);
}

// === ControladorClienteABM ===
void ControladorClienteABM::botonVolver_Click(Object^ sender, EventArgs^ e) {
    gcnew ControladorAdmin(this->usuario, this->ventanaPrincipal);
}

void ControladorClienteABM::mostrarFacturasButton_Click(Object^ sender, EventArgs^ e) {
    if (this->vista->tablaClientes->SelectedRows->Count == 0) {
        MessageBox::Show(L"Seleccione un cliente de la tabla");
        return;
    }
    auto fila = this->vista->tablaClientes->SelectedRows[0];
    int idCliente = safe_cast<int>(fila->Cells[0]->Value);
    String^ nombre = fila->Cells[1]->Value->ToString();
    String^ apellido = fila->Cells[2]->Value->ToString();
    gcnew ControladorFactura(this->usuario, this->ventanaPrincipal, idCliente, nombre, apellido);
}

// === ControladorDepositoABM ===
void ControladorDepositoABM::volverButton_Click(Object^ sender, EventArgs^ e) {
    if (this->usuario->Rol == L"Deposito") gcnew ControladorLogin(this->ventanaPrincipal);
    else gcnew ControladorAdmin(this->usuario, this->ventanaPrincipal);
}

// === ControladorProveedorABM ===
void ControladorProveedorABM::volverButton_Click(Object^ sender, EventArgs^ e) {
    if (this->usuario->Rol == L"Deposito") gcnew ControladorLogin(this->ventanaPrincipal);
    else gcnew ControladorAdmin(this->usuario, this->ventanaPrincipal);
}

// === ControladorUsuarioABM ===
void ControladorUsuarioABM::volverButton_Click(Object^ sender, EventArgs^ e) {
    gcnew ControladorAdmin(this->usuario, this->ventanaPrincipal);
}

// === ControladorRegistro ===
void ControladorRegistro::registrarse_Click(Object^ sender, EventArgs^ e) {
    String^ error = ValidadorCampos::validarRequeridos(
        L"Nombre", this->vistaRegistro->nombreTF->Text,
        L"Apellido", this->vistaRegistro->apellidoTF->Text,
        L"DNI", this->vistaRegistro->dniTF->Text,
        L"Telefono", this->vistaRegistro->telefonoTF->Text,
        L"Direccion", this->vistaRegistro->direccionTF->Text,
        L"Mail", this->vistaRegistro->mailTF->Text,
        L"Password", this->vistaRegistro->password->Text
    );
    if (error != nullptr) { MessageBox::Show(L"Campos requeridos: " + error); return; }
    if (!ValidadorMail::esValido(this->vistaRegistro->mailTF->Text)) { MessageBox::Show(L"Mail invalido"); return; }
    if (this->vistaRegistro->password->Text->Length < 6) { MessageBox::Show(L"La contrasena debe tener al menos 6 caracteres"); return; }
    if (this->registrar(
        this->vistaRegistro->nombreTF->Text,
        this->vistaRegistro->apellidoTF->Text,
        this->vistaRegistro->dniTF->Text,
        this->vistaRegistro->telefonoTF->Text,
        this->vistaRegistro->direccionTF->Text,
        this->vistaRegistro->mailTF->Text,
        this->vistaRegistro->password->Text
    )) {
        gcnew ControladorLogin(this->ventanaPrincipal);
        MessageBox::Show(L"Logee");
    }
}

void ControladorRegistro::botonVolver_Click(Object^ sender, EventArgs^ e) {
    gcnew ControladorLogin(this->ventanaPrincipal);
}
