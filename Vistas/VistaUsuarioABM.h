#pragma once
#include "..\Filtros\FiltroNumerico.h"

using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace Filtros;

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
            auto azul = Color::LightSkyBlue;

            panelUsuarioABM = gcnew Panel();
            panelUsuarioABM->Size = System::Drawing::Size(800, 600);

            comboBoxFiltroHabilitado = gcnew ComboBox();
            comboBoxFiltroHabilitado->Items->Add(L"Habilitados");
            comboBoxFiltroHabilitado->Items->Add(L"Deshabilitados");
            comboBoxFiltroHabilitado->DropDownStyle = ComboBoxStyle::DropDownList;
            comboBoxFiltroHabilitado->Location = Point(15, 15);
            comboBoxFiltroHabilitado->Size = System::Drawing::Size(120, 25);
            panelUsuarioABM->Controls->Add(comboBoxFiltroHabilitado);
            comboBoxFiltroHabilitado->SelectedIndex = 0;

            auto lblDNI = gcnew Label();
            lblDNI->Text = L"DNI Usuario:";
            lblDNI->Location = Point(145, 15);
            lblDNI->Size = System::Drawing::Size(80, 25);
            lblDNI->TextAlign = ContentAlignment::MiddleLeft;
            panelUsuarioABM->Controls->Add(lblDNI);

            dniTF = gcnew TextBox();
            dniTF->Location = Point(230, 15);
            dniTF->Size = System::Drawing::Size(100, 25);
            panelUsuarioABM->Controls->Add(dniTF);
            FiltroNumerico::Aplicar(dniTF);

            botonBuscar = gcnew Button();
            botonBuscar->Text = L"Buscar";
            botonBuscar->Location = Point(340, 15);
            botonBuscar->Size = System::Drawing::Size(80, 25);
            botonBuscar->BackColor = azul;
            panelUsuarioABM->Controls->Add(botonBuscar);

            agregarButton = gcnew Button();
            agregarButton->Text = L"Agregar";
            agregarButton->Location = Point(15, 55);
            agregarButton->Size = System::Drawing::Size(90, 30);
            agregarButton->BackColor = azul;
            panelUsuarioABM->Controls->Add(agregarButton);

            modificarButton = gcnew Button();
            modificarButton->Text = L"Modificar";
            modificarButton->Location = Point(115, 55);
            modificarButton->Size = System::Drawing::Size(90, 30);
            modificarButton->BackColor = azul;
            panelUsuarioABM->Controls->Add(modificarButton);

            eliminarButton = gcnew Button();
            eliminarButton->Text = L"Deshabilitar";
            eliminarButton->Location = Point(215, 55);
            eliminarButton->Size = System::Drawing::Size(90, 30);
            eliminarButton->BackColor = azul;
            panelUsuarioABM->Controls->Add(eliminarButton);

            volverButton = gcnew Button();
            volverButton->Text = L"Volver";
            volverButton->Location = Point(680, 55);
            volverButton->Size = System::Drawing::Size(100, 30);
            volverButton->BackColor = Color::Gainsboro;
            panelUsuarioABM->Controls->Add(volverButton);

            tablaUsuarios = gcnew DataGridView();
            tablaUsuarios->Location = Point(15, 100);
            tablaUsuarios->Size = System::Drawing::Size(770, 480);
            tablaUsuarios->AllowUserToAddRows = false;
            tablaUsuarios->AllowUserToDeleteRows = false;
            tablaUsuarios->ReadOnly = true;
            tablaUsuarios->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            tablaUsuarios->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            panelUsuarioABM->Controls->Add(tablaUsuarios);
        }
    };
}
