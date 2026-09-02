#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "algo.h"

#include <algorithm>
#include <random>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    std::random_device rd;
    deque_model_.random_gen.seed(rd());

    ApplyModel();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::ApplyModel() {
    ui->list_widget->blockSignals(true);

    auto preserve_iter = deque_model_.iterator;

    ui->list_widget->clear();

    size_t index = 0;
    for (auto it = deque_model_.items.begin(); it != deque_model_.items.end(); ++it) {
        QString item_text = QString::number(index) + ": " + QString::fromStdString(*it);
        ui->list_widget->addItem(item_text);
        ++index;
    }

    ui->list_widget->addItem("end");

    deque_model_.iterator = preserve_iter;

    ui->txt_size->setText(QString::number(deque_model_.items.size()));

    bool empty = deque_model_.items.empty();
    ui->btn_pop_front->setDisabled(empty);
    ui->btn_pop_back->setDisabled(empty);

    ui->list_widget->blockSignals(false);

    ApplyIterator();
}

void MainWindow::ApplyIterator() {
    int offset = static_cast<int>(std::distance(deque_model_.items.begin(),
                                                deque_model_.iterator));

    ui->list_widget->setCurrentRow(offset);

    bool is_end = deque_model_.iterator == deque_model_.items.end();

    ui->btn_edit->setDisabled(is_end);
    ui->btn_erase->setDisabled(is_end);
    ui->btn_inc->setDisabled(is_end);

    bool is_begin = deque_model_.iterator == deque_model_.items.begin();
    ui->btn_dec->setDisabled(is_begin);

    if (is_end) {
        ui->txt_elem_content->clear();
    } else {
        ui->txt_elem_content->setText(QString::fromStdString(*deque_model_.iterator));
    }
}

void MainWindow::on_btn_push_front_clicked() {
    QString new_item = ui->txt_elem_content->text();
    if (new_item.isEmpty()) {
        return;
    }
    deque_model_.items.push_front(new_item.toStdString());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_btn_push_back_clicked() {
    QString new_item = ui->txt_elem_content->text();
    if (new_item.isEmpty()) {
        return;
    }
    deque_model_.items.push_back(new_item.toStdString());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_btn_pop_front_clicked() {
    if (deque_model_.items.empty()) {
        return;
    }
    deque_model_.items.pop_front();
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_btn_pop_back_clicked() {
    if (deque_model_.items.empty()) {
        return;
    }
    deque_model_.items.pop_back();
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_btn_clear_clicked() {
    deque_model_.items.clear();
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_btn_tea_clicked() {
    static std::deque<std::string> tea = {
        "Чай Лунцзин",
        "Эрл Грей",
        "Сенча",
        "Пуэр",
        "Дарджилинг",
        "Ассам",
        "Матча",
        "Ганпаудер",
        "Оолонг",
        "Лапсанг Сушонг"
    };
    deque_model_.items = tea;
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_btn_cakes_clicked() {
    static std::deque<std::string> cakes = {
        "Красный бархат",
        "Наполеон",
        "Медовик",
        "Тирамису",
        "Прага",
        "Чизкейк",
        "Захер",
        "Эстерхази",
        "Морковный торт",
        "Чёрный лес"
    };
    deque_model_.items = cakes;
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_btn_insert_clicked() {
    QString new_item = ui->txt_elem_content->text();
    if (new_item.isEmpty()) {
        return;
    }
    deque_model_.items.insert(deque_model_.iterator, new_item.toStdString());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_btn_erase_clicked() {
    if (deque_model_.iterator == deque_model_.items.end() || deque_model_.items.empty()) {
        return;
    }
    deque_model_.iterator = deque_model_.items.erase(deque_model_.iterator);
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_btn_edit_clicked() {
    if (deque_model_.iterator == deque_model_.items.end()) {
        return;
    }
    QString new_text = ui->txt_elem_content->text();
    if (new_text.isEmpty()) {
        return;
    }
    *deque_model_.iterator = new_text.toStdString();
    ApplyModel();
}

void MainWindow::on_btn_begin_clicked() {
    deque_model_.iterator = deque_model_.items.begin();
    ApplyIterator();
}

void MainWindow::on_btn_end_clicked() {
    deque_model_.iterator = deque_model_.items.end();
    ApplyIterator();
}

void MainWindow::on_btn_inc_clicked() {
    if (deque_model_.iterator != deque_model_.items.end()) {
        ++deque_model_.iterator;
        ApplyIterator();
    }
}

void MainWindow::on_btn_dec_clicked() {
    if (deque_model_.iterator != deque_model_.items.begin()) {
        --deque_model_.iterator;
        ApplyIterator();
    }
}

void MainWindow::on_list_widget_currentRowChanged(int currentRow) {
    if (currentRow < 0 || currentRow > static_cast<int>(deque_model_.items.size())) {
        return;
    }

    deque_model_.iterator = deque_model_.items.begin();
    std::advance(deque_model_.iterator, currentRow);
    ApplyIterator();
}

void MainWindow::on_btn_find_clicked() {
    QString search_text = ui->txt_elem_content->text();
    if (search_text.isEmpty()) {
        return;
    }
    auto it = std::find(deque_model_.items.begin(),
                        deque_model_.items.end(),
                        search_text.toStdString());
    deque_model_.iterator = it;
    ApplyIterator();
}

void MainWindow::on_btn_count_clicked() {
    QString search_text = ui->le_count->text();
    if (search_text.isEmpty()) {
        return;
    }
    size_t count = std::count(deque_model_.items.begin(),
                              deque_model_.items.end(),
                              search_text.toStdString());
    ui->lbl_count->setText(QString::number(count));
}

void MainWindow::on_btn_min_element_clicked() {
    if (deque_model_.items.empty()) {
        return;
    }
    auto it = std::min_element(deque_model_.items.begin(),
                               deque_model_.items.end());
    deque_model_.iterator = it;
    ApplyIterator();
}

void MainWindow::on_btn_max_element_clicked() {
    if (deque_model_.items.empty()) {
        return;
    }
    auto it = std::max_element(deque_model_.items.begin(),
                               deque_model_.items.end());
    deque_model_.iterator = it;
    ApplyIterator();
}

void MainWindow::on_btn_sort_clicked() {
    deque_model_.items = MergeSort(deque_model_.items, std::less<std::string>());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_btn_sOrT_clicked() {
    auto comparator = [](const std::string& a, const std::string& b) {
        return QString::compare(QString::fromStdString(a),
                               QString::fromStdString(b),
                               Qt::CaseInsensitive) < 0;
    };
    deque_model_.items = MergeSort(deque_model_.items, comparator);
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_btn_shuffle_clicked() {
    std::shuffle(deque_model_.items.begin(),
                 deque_model_.items.end(),
                 deque_model_.random_gen);
    ApplyModel();
}

void MainWindow::on_btn_unique_clicked() {
    if (!std::is_sorted(deque_model_.items.begin(), deque_model_.items.end())) {
        return;
    }

    auto new_end = std::unique(deque_model_.items.begin(), deque_model_.items.end());
    deque_model_.items.erase(new_end, deque_model_.items.end());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_btn_reverse_clicked() {
    std::reverse(deque_model_.items.begin(), deque_model_.items.end());
    ApplyModel();
}

void MainWindow::on_btn_lower_bound_clicked() {
    QString bound = ui->txt_elem_content->text();
    if (bound.isEmpty()) {
        return;
    }

    if (!std::is_sorted(deque_model_.items.begin(), deque_model_.items.end())) {
        return;
    }

    auto it = std::lower_bound(deque_model_.items.begin(),
                               deque_model_.items.end(),
                               bound.toStdString());
    deque_model_.iterator = it;
    ApplyIterator();
}

void MainWindow::on_btn_upper_bound_clicked() {
    QString bound = ui->txt_elem_content->text();
    if (bound.isEmpty()) {
        return;
    }

    if (!std::is_sorted(deque_model_.items.begin(), deque_model_.items.end())) {
        return;
    }

    auto it = std::upper_bound(deque_model_.items.begin(),
                               deque_model_.items.end(),
                               bound.toStdString());
    deque_model_.iterator = it;
    ApplyIterator();
}
