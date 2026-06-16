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

        VistaAdmin() {
            panelAdmin = gcnew Panel();
            panelAdmin->Size = System::Drawing::Size(800, 600);

            auto lblTitulo = gcnew Label();
            lblTitulo->Text = L"Panel de Administracion";
            lblTitulo->Font = gcnew System::Drawing::Font(L"Arial", 16);
            lblTitulo->Location = Point(250, 100);
            lblTitulo->Size = System::Drawing::Size(300, 40);
            panelAdmin->Controls->Add(lblTitulo);

            botonAdministrarUsuarios = gcnew Button();
            botonAdministrarUsuarios->Text = L"Administrar Usuarios";
            botonAdministrarUsuarios->Location = Point(280, 170);
            botonAdministrarUsuarios->Size = System::Drawing::Size(200, 40);
            panelAdmin->Controls->Add(botonAdministrarUsuarios);

            botonAdministrarClientes = gcnew Button();
            botonAdministrarClientes->Text = L"Administrar Clientes";
            botonAdministrarClientes->Location = Point(280, 220);
            botonAdministrarClientes->Size = System::Drawing::Size(200, 40);
            panelAdmin->Controls->Add(botonAdministrarClientes);

            botonFacturar = gcnew Button();
            botonFacturar->Text = L"Facturar";
            botonFacturar->Location = Point(280, 270);
            botonFacturar->Size = System::Drawing::Size(200, 40);
            panelAdmin->Controls->Add(botonFacturar);

            botonAdministrarDeposito = gcnew Button();
            botonAdministrarDeposito->Text = L"Administrar Deposito";
            botonAdministrarDeposito->Location = Point(280, 320);
            botonAdministrarDeposito->Size = System::Drawing::Size(200, 40);
            panelAdmin->Controls->Add(botonAdministrarDeposito);

            cerrarSesion = gcnew Button();
            cerrarSesion->Text = L"Cerrar Sesion";
            cerrarSesion->Location = Point(280, 380);
            cerrarSesion->Size = System::Drawing::Size(200, 40);
            panelAdmin->Controls->Add(cerrarSesion);
        }
    };
}
