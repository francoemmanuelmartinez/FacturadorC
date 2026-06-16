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
            panelFactura = gcnew Panel();
            panelFactura->Size = System::Drawing::Size(800, 600);

            labelTitulo = gcnew Label();
            labelTitulo->Font = gcnew System::Drawing::Font(L"Arial", 14);
            labelTitulo->Location = Point(20, 20);
            labelTitulo->Size = System::Drawing::Size(500, 30);
            panelFactura->Controls->Add(labelTitulo);

            tableFacturas = gcnew DataGridView();
            tableFacturas->Location = Point(20, 60);
            tableFacturas->Size = System::Drawing::Size(740, 400);
            tableFacturas->AllowUserToAddRows = false;
            tableFacturas->AllowUserToDeleteRows = false;
            tableFacturas->ReadOnly = true;
            tableFacturas->SelectionMode = DataGridViewSelectionMode::FullRowSelect;
            tableFacturas->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
            panelFactura->Controls->Add(tableFacturas);

            verDetalleButton = gcnew Button();
            verDetalleButton->Text = L"Ver Detalle";
            verDetalleButton->Location = Point(20, 480);
            verDetalleButton->Size = System::Drawing::Size(120, 30);
            panelFactura->Controls->Add(verDetalleButton);

            volverButton = gcnew Button();
            volverButton->Text = L"Volver";
            volverButton->Location = Point(680, 480);
            volverButton->Size = System::Drawing::Size(100, 30);
            panelFactura->Controls->Add(volverButton);
        }
    };
}
