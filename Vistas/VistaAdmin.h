#pragma once

using namespace System::Drawing;
using namespace System::Windows::Forms;

namespace Vistas {
    public ref class VistaAdmin {
    public:
        Panel^ panelAdmin;
        Button^ cerrarSesion;
        Button^ botonFacturar;
        Button^ botonAdministrarUsuarios;
        Button^ botonAdministrarClientes;
        Button^ botonAdministrarDeposito;
        Button^ botonAdministrarProveedores;

        VistaAdmin() {
            auto azul = Color::LightSkyBlue;

            panelAdmin = gcnew Panel();
            panelAdmin->Size = System::Drawing::Size(800, 600);

            auto lblTitulo = gcnew Label();
            lblTitulo->Text = L"Panel Administrador";
            lblTitulo->Font = gcnew System::Drawing::Font(L"Arial", 16, FontStyle::Bold);
            lblTitulo->Location = Point(20, 15);
            lblTitulo->Size = System::Drawing::Size(300, 30);
            lblTitulo->TextAlign = ContentAlignment::MiddleLeft;
            panelAdmin->Controls->Add(lblTitulo);

            cerrarSesion = gcnew Button();
            cerrarSesion->Text = L"Cerrar Sesion";
            cerrarSesion->Location = Point(670, 15);
            cerrarSesion->Size = System::Drawing::Size(120, 30);
            cerrarSesion->BackColor = azul;
            panelAdmin->Controls->Add(cerrarSesion);

            botonAdministrarUsuarios = gcnew Button();
            botonAdministrarUsuarios->Text = L"Administrar Usuarios";
            botonAdministrarUsuarios->Location = Point(150, 80);
            botonAdministrarUsuarios->Size = System::Drawing::Size(200, 45);
            botonAdministrarUsuarios->BackColor = azul;
            panelAdmin->Controls->Add(botonAdministrarUsuarios);

            botonAdministrarClientes = gcnew Button();
            botonAdministrarClientes->Text = L"Administrar Clientes";
            botonAdministrarClientes->Location = Point(150, 140);
            botonAdministrarClientes->Size = System::Drawing::Size(200, 45);
            botonAdministrarClientes->BackColor = azul;
            panelAdmin->Controls->Add(botonAdministrarClientes);

            botonFacturar = gcnew Button();
            botonFacturar->Text = L"Facturar";
            botonFacturar->Location = Point(400, 140);
            botonFacturar->Size = System::Drawing::Size(200, 45);
            botonFacturar->BackColor = azul;
            panelAdmin->Controls->Add(botonFacturar);

            botonAdministrarProveedores = gcnew Button();
            botonAdministrarProveedores->Text = L"Administrar Proveedores";
            botonAdministrarProveedores->Location = Point(150, 200);
            botonAdministrarProveedores->Size = System::Drawing::Size(200, 45);
            botonAdministrarProveedores->BackColor = azul;
            panelAdmin->Controls->Add(botonAdministrarProveedores);

            botonAdministrarDeposito = gcnew Button();
            botonAdministrarDeposito->Text = L"Administrar Deposito";
            botonAdministrarDeposito->Location = Point(400, 200);
            botonAdministrarDeposito->Size = System::Drawing::Size(200, 45);
            botonAdministrarDeposito->BackColor = azul;
            panelAdmin->Controls->Add(botonAdministrarDeposito);
        }
    };
}
