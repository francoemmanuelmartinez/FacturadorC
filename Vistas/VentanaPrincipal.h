#pragma once

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;

namespace Vistas {
    public ref class VentanaPrincipal : public Form {
    private:
        Panel^ panelActual;
        void CentrarPanel() {
            if (panelActual != nullptr) {
                panelActual->Location = Point(
                    Math::Max(0, (this->ClientSize.Width - panelActual->Width) / 2),
                    Math::Max(0, (this->ClientSize.Height - panelActual->Height) / 2)
                );
            }
        }
    public:
        VentanaPrincipal() {
            this->Size = System::Drawing::Size(800, 630);
            this->StartPosition = FormStartPosition::CenterScreen;
            this->Text = L"Facturador";
        }

        void setVista(Panel^ panel) {
            this->Controls->Clear();
            panelActual = panel;
            this->Controls->Add(panel);
            CentrarPanel();
        }

    protected:
        void OnResize(EventArgs^ e) override {
            Form::OnResize(e);
            CentrarPanel();
        }
    };
}
