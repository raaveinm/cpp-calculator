#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->cmb_controller->addItems(QStringList{
        "double",
        "float",
        "uint8_t",
        "int",
        "int64_t",
        "size_t",
        "Rational"
    });

    SetInputText("0");
    SetFormulaText("");
    SetMemText("");
    ui->tb_extra->setVisible(false);

    connect(
        ui->cmb_controller,
        QOverload<int>::of(&QComboBox::currentIndexChanged),
        this,
        &MainWindow::on_cmb_controller_currentIndexChanged);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::SetInputText(const std::string& text) {
    ui->l_result->setStyleSheet("");
	ui->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetErrorText(const std::string& text) {
    ui->l_result->setStyleSheet("color: red;");
    ui->l_result->setText(QString::fromStdString(text));
}

void MainWindow::SetFormulaText(const std::string& text) {
    ui->l_formula->setText(QString::fromStdString(text));
}

void MainWindow::SetExtraKey(const std::optional<std::string>& key) {
    if (key.has_value()) {
        ui->tb_extra->setText(QString::fromStdString(key.value()));
        ui->tb_extra->setVisible(true);
    } else {
        ui->tb_extra->setVisible(false);
    }
}

void MainWindow::SetMemText(const std::string& text) {
    ui->l_memory->setText(QString::fromStdString(text));
}

void MainWindow::SetDigitKeyCallback(std::function<void(int key)> cb) {
    digit_callback_ = std::move(cb);
}

void MainWindow::SetProcessOperationKeyCallback(std::function<void(Operation key)> cb) {
    operation_callback_ = std::move(cb);
}

void MainWindow::SetProcessControlKeyCallback(std::function<void(ControlKey key)> cb) {
    control_callback_ = std::move(cb);
}

void MainWindow::SetControllerCallback(std::function<void(ControllerType controller)> cb) {
    controller_callback_ = std::move(cb);
}

void MainWindow::on_btn_1_clicked() { if (digit_callback_) digit_callback_(1); }
void MainWindow::on_btn_2_clicked() { if (digit_callback_) digit_callback_(2); }
void MainWindow::on_btn_3_clicked() { if (digit_callback_) digit_callback_(3); }
void MainWindow::on_btn_4_clicked() { if (digit_callback_) digit_callback_(4); }
void MainWindow::on_btn_5_clicked() { if (digit_callback_) digit_callback_(5); }
void MainWindow::on_btn_6_clicked() { if (digit_callback_) digit_callback_(6); }
void MainWindow::on_btn_7_clicked() { if (digit_callback_) digit_callback_(7); }
void MainWindow::on_btn_8_clicked() { if (digit_callback_) digit_callback_(8); }
void MainWindow::on_btn_9_clicked() { if (digit_callback_) digit_callback_(9); }
void MainWindow::on_btn_0_clicked() { if (digit_callback_) digit_callback_(0); }

void MainWindow::on_btn_in_pow_clicked() { if (operation_callback_) operation_callback_(Operation::POWER); }
void MainWindow::on_btn_division_clicked() { if (operation_callback_) operation_callback_(Operation::DIVISION); }
void MainWindow::on_btn_multiply_clicked() { if (operation_callback_) operation_callback_(Operation::MULTIPLICATION); }
void MainWindow::on_btn_subtract_clicked() { if (operation_callback_) operation_callback_(Operation::SUBTRACTION); }
void MainWindow::on_btn_addition_clicked() { if (operation_callback_) operation_callback_(Operation::ADDITION); }

void MainWindow::on_btn_erase_clicked() { if (control_callback_) control_callback_(ControlKey::BACKSPACE); }
void MainWindow::on_btn_plus_minus_clicked() { if (control_callback_) control_callback_(ControlKey::PLUS_MINUS); }
void MainWindow::on_btn_res_clicked() { if (control_callback_) control_callback_(ControlKey::EQUALS); }
void MainWindow::on_btn_clear_clicked() { if (control_callback_) control_callback_(ControlKey::CLEAR); }
void MainWindow::on_btn_ms_clicked() { if (control_callback_) control_callback_(ControlKey::MEM_SAVE); }
void MainWindow::on_btn_mc_clicked() { if (control_callback_) control_callback_(ControlKey::MEM_CLEAR); }
void MainWindow::on_bt_mr_clicked() { if (control_callback_) control_callback_(ControlKey::MEM_LOAD); }
void MainWindow::on_tb_extra_clicked() { if (control_callback_) control_callback_(ControlKey::EXTRA_KEY); }

void MainWindow::on_cmb_controller_currentIndexChanged(int index) {
    if (controller_callback_) {
        switch (index) {
            case 0: controller_callback_(ControllerType::DOUBLE); break;
            case 1: controller_callback_(ControllerType::FLOAT); break;
            case 2: controller_callback_(ControllerType::UINT8_T); break;
            case 3: controller_callback_(ControllerType::INT); break;
            case 4: controller_callback_(ControllerType::INT64_T); break;
            case 5: controller_callback_(ControllerType::SIZE_T); break;
            case 6: controller_callback_(ControllerType::RATIONAL); break;
            default: break;
        }
    }
}
