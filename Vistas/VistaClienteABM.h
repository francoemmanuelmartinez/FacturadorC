#pragma once
#include "..\Filtros\FiltroNumerico.h"

using namespace System::Drawing;
using namespace System::Windows::Forms;
using namespace Filtros;

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
            auto azul = Color::LightSkyBlue;

            panelClienteABM = gcnew Panel();
            panelClienteABM->Size = System::Drawing::Size(800, 600);

            comboBoxFiltroHabilitado = gcnew ComboBox();
            comboBoxFiltroHabilitado->Items->Add(L"Habilitados");
            comboBoxFiltroHabilitado->Items->Add(L"Deshabilitados");
            comboBoxFiltroHabilitado->DropDownStyle = ComboBoxStyle::DropDownList;
            comboBoxFiltroHabilitado->Location = Point(15, 15);
            comboBoxFiltroHabilitado->Size = System::Drawing::Size(120, 25);
            panelClienteABM->Controls->Add(comboBoxFiltroHabilitado);
            comboBoxFiltroHabilitado->SelectedIndex = 0;

            auto lblDNI = gcnew Label();
            lblDNI->Text = L"DNI Cliente:";
            lblDNI->Location = Point(145, 15);
            lblDNI->Size = System::Drawing::Size(80, 25);
            lblDNI->TextAlign = ContentAlignment::MiddleLeft;
            panelClienteABM->Controls->Add(lblDNI);

            dniTF = gcnew TextBox();
            dniTF->Location = Point(230, 15);
            dniTF->Size = System::Drawing::Size(100, 25);
            panelClienteABM->Controls->Add(dniTF);
            FiltroNumerico::Aplicar(dniTF);

            botonBuscar = gcnew Button();
            botonBuscar->Text = L"Buscar";
            botonBuscar->Location = Point(340, 15);
            botonBuscar->Size = System::Drawing::Size(80, 25);
            botonBuscar->BackColor = azul;
            panelClienteABM->Controls->Add(botonBuscar);

            agregarButton = gcnew Button();
            agregarButton->Text = L"Agregar";
            agregarButton->Location = Point(15, 55);
            agregarButton->Size = System::Drawing::Size(90, 30);
            agregarButton->BackColor = azul;
            panelClienteABM->Controls->Add(agregarButton);

            modificarButton = gcnew Button();
            modificarButton->Text = L"Modificar";
            modificarButton->Location = Point(115, 55);
            modificarButton->Size = System::Drawing::Size(90, 30);
            modificarButton->BackColor = azul;
            panelClienteABM->Controls->Add(modificarButton);

            eliminarButton = gcnew Button();
            eliminarButton->Text = L"Deshabilitar";
            eliminarButton->Location = Point(215, 55);
            eliminarButton->Size = System::Drawing::Size(90, 30);
            eliminarButton->BackColor = azul;
            panelClienteABM->Controls->Add(eliminarButton);

            mostrarFacturasButton = gcnew Button();
            mostrarFacturasButton->Text = L"Ver Facturas";
            mostrarFacturasButton->Location = Point(315, 55);
            mostrarFacturasButton->Size = System::Drawing::Size(100, 30);
            mostrarFacturasButton->BackColor = Color::FromArgb(255, 200, 100);
            panelClienteABM->Controls->Add(mostrarFacturasButton);

            botonVolver = gcnew Button();
            botonVolver->Text = L"Volver";
            botonVolver->Location = Point(680, 55);
            botonVolver->Size = System::Drawing::Size(100, 30);
            botonVolver->BackColor = Color::Gainsboro;
            panelClienteABM->Controls->Add(botonVolver);

            tablaClientes = gcnew DataGridView();
            tablaClientes->Location = Point(15, 100);
            tablaClientes->Size = System::Drawing::Size(770, 480);
            tablaClientes->AllowUserToAddRows = false;
            tablaClientes->AllowUserToDeleteRows = false;
            tablaClientes->ReadOnly = true;
            tablaClientes->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            tablaClientes->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            panelClienteABM->Controls->Add(tablaClientes);
        }
    };
}
