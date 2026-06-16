#pragma once

using namespace System::Drawing;
using namespace System::Windows::Forms;

namespace Vistas {
    public ref class VistaClienteABM {
    public:
        Panel^ panelClienteABM;
        DataGridView^ tablaClientes;
        TextBox^ dniTF;
        Button^ botonBuscar;
        Button^ eliminarButton;
        Button^ modificarButton;
        Button^ agregarButton;
        Button^ botonVolver;
        ComboBox^ comboBoxFiltroHabilitado;
        Button^ mostrarFacturasButton;

        VistaClienteABM() {
            panelClienteABM = gcnew Panel();
            panelClienteABM->Size = System::Drawing::Size(800, 600);

            auto lblTitulo = gcnew Label();
            lblTitulo->Text = L"Gestion de Clientes";
            lblTitulo->Font = gcnew System::Drawing::Font(L"Arial", 14);
            lblTitulo->Location = Point(250, 20);
            lblTitulo->Size = System::Drawing::Size(250, 30);
            panelClienteABM->Controls->Add(lblTitulo);

            auto lblFiltro = gcnew Label();
            lblFiltro->Text = L"Filtro:";
            lblFiltro->Location = Point(20, 60);
            lblFiltro->Size = System::Drawing::Size(50, 20);
            panelClienteABM->Controls->Add(lblFiltro);

            comboBoxFiltroHabilitado = gcnew ComboBox();
            comboBoxFiltroHabilitado->Location = Point(70, 60);
            comboBoxFiltroHabilitado->Size = System::Drawing::Size(120, 20);
            comboBoxFiltroHabilitado->Items->Add(L"Habilitados");
            comboBoxFiltroHabilitado->Items->Add(L"Deshabilitados");
            panelClienteABM->Controls->Add(comboBoxFiltroHabilitado);

            auto lblDNI = gcnew Label();
            lblDNI->Text = L"DNI:";
            lblDNI->Location = Point(220, 60);
            lblDNI->Size = System::Drawing::Size(40, 20);
            panelClienteABM->Controls->Add(lblDNI);

            dniTF = gcnew TextBox();
            dniTF->Location = Point(260, 60);
            dniTF->Size = System::Drawing::Size(120, 20);
            panelClienteABM->Controls->Add(dniTF);

            botonBuscar = gcnew Button();
            botonBuscar->Text = L"Buscar";
            botonBuscar->Location = Point(390, 58);
            botonBuscar->Size = System::Drawing::Size(80, 25);
            panelClienteABM->Controls->Add(botonBuscar);

            tablaClientes = gcnew DataGridView();
            tablaClientes->Location = Point(20, 100);
            tablaClientes->Size = System::Drawing::Size(740, 350);
            tablaClientes->AllowUserToAddRows = false;
            tablaClientes->AllowUserToDeleteRows = false;
            tablaClientes->ReadOnly = true;
            tablaClientes->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            tablaClientes->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            panelClienteABM->Controls->Add(tablaClientes);

            agregarButton = gcnew Button();
            agregarButton->Text = L"Agregar";
            agregarButton->Location = Point(20, 470);
            agregarButton->Size = System::Drawing::Size(100, 30);
            panelClienteABM->Controls->Add(agregarButton);

            modificarButton = gcnew Button();
            modificarButton->Text = L"Modificar";
            modificarButton->Location = Point(130, 470);
            modificarButton->Size = System::Drawing::Size(100, 30);
            panelClienteABM->Controls->Add(modificarButton);

            eliminarButton = gcnew Button();
            eliminarButton->Text = L"Deshabilitar";
            eliminarButton->Location = Point(240, 470);
            eliminarButton->Size = System::Drawing::Size(100, 30);
            panelClienteABM->Controls->Add(eliminarButton);

            mostrarFacturasButton = gcnew Button();
            mostrarFacturasButton->Text = L"Ver Facturas";
            mostrarFacturasButton->Location = Point(350, 470);
            mostrarFacturasButton->Size = System::Drawing::Size(100, 30);
            panelClienteABM->Controls->Add(mostrarFacturasButton);

            botonVolver = gcnew Button();
            botonVolver->Text = L"Volver";
            botonVolver->Location = Point(680, 470);
            botonVolver->Size = System::Drawing::Size(100, 30);
            panelClienteABM->Controls->Add(botonVolver);
        }
    };
}
