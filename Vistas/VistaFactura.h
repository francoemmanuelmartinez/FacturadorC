#pragma once

using namespace System::Drawing;
using namespace System::Windows::Forms;

namespace Vistas {
    public ref class VistaFactura {
    public:
        Panel^ panelFactura;
        DataGridView^ tableFacturas;
        Button^ verDetalleButton;
        Button^ volverButton;
        Label^ labelTitulo;

        VistaFactura() {
            auto azul = Color::LightSkyBlue;

            panelFactura = gcnew Panel();
            panelFactura->Size = System::Drawing::Size(800, 600);

            verDetalleButton = gcnew Button();
            verDetalleButton->Text = L"Ver Detalle";
            verDetalleButton->Location = Point(15, 15);
            verDetalleButton->Size = System::Drawing::Size(120, 30);
            verDetalleButton->BackColor = azul;
            panelFactura->Controls->Add(verDetalleButton);

            volverButton = gcnew Button();
            volverButton->Text = L"Volver";
            volverButton->Location = Point(680, 15);
            volverButton->Size = System::Drawing::Size(100, 30);
            volverButton->BackColor = Color::Gainsboro;
            panelFactura->Controls->Add(volverButton);

            labelTitulo = gcnew Label();
            labelTitulo->Font = gcnew System::Drawing::Font(L"Arial", 16, FontStyle::Bold);
            labelTitulo->TextAlign = ContentAlignment::MiddleCenter;
            labelTitulo->Location = Point(200, 15);
            labelTitulo->Size = System::Drawing::Size(400, 30);
            panelFactura->Controls->Add(labelTitulo);

            tableFacturas = gcnew DataGridView();
            tableFacturas->Location = Point(15, 60);
            tableFacturas->Size = System::Drawing::Size(770, 520);
            tableFacturas->AllowUserToAddRows = false;
            tableFacturas->AllowUserToDeleteRows = false;
            tableFacturas->ReadOnly = true;
            tableFacturas->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            tableFacturas->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            panelFactura->Controls->Add(tableFacturas);
        }
    };
}
