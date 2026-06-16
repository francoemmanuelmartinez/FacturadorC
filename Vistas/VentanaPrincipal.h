#pragma once

using namespace System::Windows::Forms;

namespace Vistas {
    public ref class VentanaPrincipal : public Form {
    public:
        VentanaPrincipal() {
            this->Size = System::Drawing::Size(800, 600);
            this->StartPosition = FormStartPosition::CenterScreen;
            this->Text = L"Facturador";
        }

        void setVista(Panel^ panel) {
            this->Controls->Clear();
            this->Controls->Add(panel);
            this->Refresh();
        }
    };
}
