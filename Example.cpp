#include <UserInterface.h>

#include <string_format>

UserInterface::UITab*     tab1         = nullptr;
UserInterface::UIWindow*  window       = nullptr;
UserInterface::UIWindow*  window2      = nullptr;
UserInterface::UITextbox* textbox      = nullptr;
UserInterface::UITextbox* tab1_textbox = nullptr;
UserInterface::UITextbox* tab2_textbox = nullptr;

UI_Main {
    auto* ui  = UserInterface::GetAPI();
    auto* app = ui->GetApplication();
    window    = app->NewWindow("Window 1");
    window2   = app->NewWindow("Window 2");
    window->SetHeight(800);
    window->SetWidth(800);

    // window->AddLabel("Hi, I am a label!");
    // textbox = window->AddTextbox("Butts.");
    // window->AddButton("I am button! CLICK ME", [](auto*) {
    //     textbox->SetText("The button was pressed!");
    // });

    // window->AddButton("Show second window", [](auto*) { window2->Show(); });
    // window->AddButton("Hide second window", [](auto*) { window2->Hide(); });

    tab1       = window->AddTab("Tab 1");
    auto* tab2 = window->AddTab("Tab 2");

    tab1->AddLabel("Tab 1 label!");
    tab1_textbox = tab1->AddTextbox("Tab 1 textbox.");
    tab1->AddButton("Tab 1 button", [](auto* button) {
        tab1_textbox->SetText(string_format("The {} button was pressed!", button->GetText()).c_str()
        );
    });

    tab2->AddLabel("Butts!");
    tab2_textbox = tab2->AddTextbox("Butts.");
    tab2->AddButton("I am BUTTS! CLICK ME", [](auto*) {
        tab2_textbox->SetText("The BUTTS was pressed!");
    });

    window->Show();
    app->Run();
    return 0;
}
