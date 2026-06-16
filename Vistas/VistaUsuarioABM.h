#pragma once

using namespace System::Drawing;
using namespace System::Windows::Forms;

namespace Vistas {
    public ref class VistaUsuarioABM {
    public:
        Panel^ panelUsuarioABM;
        DataGridView^ tablaUsuarios;
        TextBox^ dniTF;
        Button^ botonBuscar;
        Button^ eliminarButton;
        Button^ modificarButton;
        Button^ agregarButton;
        ComboBox^ comboBoxFiltroHabilitado;
        Button^ volverButton;

        VistaUsuarioABM() {
            panelUsuarioABM = gcnew Panel();
            panelUsuarioABM->Size = System::Drawing::Size(800, 600);

            auto lblTitulo = gcnew Label();
            lblTitulo->Text = L"Gestion de Usuarios";
            lblTitulo->Font = gcnew System::Drawing::Font(L"Arial", 14);
            lblTitulo->Location = Point(250, 20);
            lblTitulo->Size = System::Drawing::Size(250, 30);
            panelUsuarioABM->Controls->Add(lblTitulo);

            auto lblFiltro = gcnew Label();
            lblFiltro->Text = L"Filtro:";
            lblFiltro->Location = Point(20, 60);
            lblFiltro->Size = System::Drawing::Size(50, 20);
            panelUsuarioABM->Controls->Add(lblFiltro);

            comboBoxFiltroHabilitado = gcnew ComboBox();
            comboBoxFiltroHabilitado->Location = Point(70, 60);
            comboBoxFiltroHabilitado->Size = System::Drawing::Size(120, 20);
            comboBoxFiltroHabilitado->Items->Add(L"Habilitados");
            comboBoxFiltroHabilitado->Items->Add(L"Deshabilitados");
            panelUsuarioABM->Controls->Add(comboBoxFiltroHabilitado);

            auto lblDNI = gcnew Label();
            lblDNI->Text = L"DNI:";
            lblDNI->Location = Point(220, 60);
            lblDNI->Size = System::Drawing::Size(40, 20);
            panelUsuarioABM->Controls->Add(lblDNI);

            dniTF = gcnew TextBox();
            dniTF->Location = Point(260, 60);
            dniTF->Size = System::Drawing::Size(120, 20);
            panelUsuarioABM->Controls->Add(dniTF);

            botonBuscar = gcnew Button();
            botonBuscar->Text = L"Buscar";
            botonBuscar->Location = Point(390, 58);
            botonBuscar->Size = System::Drawing::Size(80, 25);
            panelUsuarioABM->Controls->Add(botonBuscar);

            tablaUsuarios = gcnew DataGridView();
            tablaUsuarios->Location = Point(20, 100);
            tablaUsuarios->Size = System::Drawing::Size(740, 350);
            tablaUsuarios->AllowUserToAddRows = false;
            tablaUsuarios->AllowUserToDeleteRows = false;
            tablaUsuarios->ReadOnly = true;
            tablaUsuarios->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            tablaUsuarios->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            panelUsuarioABM->Controls->Add(tablaUsuarios);

            agregarButton = gcnew Button();
            agregarButton->Text = L"Agregar";
            agregarButton->Location = Point(20, 470);
            agregarButton->Size = System::Drawing::Size(100, 30);
            panelUsuarioABM->Controls->Add(agregarButton);

            modificarButton = gcnew Button();
            modificarButton->Text = L"Modificar";
            modificarButton->Location = Point(130, 470);
            modificarButton->Size = System::Drawing::Size(100, 30);
            panelUsuarioABM->Controls->Add(modificarButton);

            eliminarButton = gcnew Button();
            eliminarButton->Text = L"Deshabilitar";
            eliminarButton->Location = Point(240, 470);
            eliminarButton->Size = System::Drawing::Size(100, 30);
            panelUsuarioABM->Controls->Add(eliminarButton);

            volverButton = gcnew Button();
            volverButton->Text = L"Volver";
            volverButton->Location = Point(680, 470);
            volverButton->Size = System::Drawing::Size(100, 30);
            panelUsuarioABM->Controls->Add(volverButton);
        }
    };
}
