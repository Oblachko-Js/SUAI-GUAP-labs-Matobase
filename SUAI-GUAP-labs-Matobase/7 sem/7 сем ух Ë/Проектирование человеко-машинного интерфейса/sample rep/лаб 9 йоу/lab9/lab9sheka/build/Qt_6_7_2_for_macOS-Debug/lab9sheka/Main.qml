import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    id: mainWindow
    width: 800
    height: 600
    visible: true
    title: "ЛР9 - Пользовательский интерфейс на QML"
    color: "#2c3e50"

    // Главный контейнер
    Column {
        anchors.centerIn: parent
        spacing: 20

        // Заголовок
        Text {
            text: "Лабораторная работа №9"
            color: "white"
            font.pixelSize: 28
            font.bold: true
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Text {
            text: "Создание пользовательского интерфейса на QML"
            color: "#ecf0f1"
            font.pixelSize: 16
            anchors.horizontalCenter: parent.horizontalCenter
        }

        // Разделитель
        Rectangle {
            width: 400
            height: 2
            color: "#3498db"
            anchors.horizontalCenter: parent.horizontalCenter
        }

        // Поле ввода - ИСПРАВЛЕНО (черный текст)
        TextField {
            id: nameInput
            placeholderText: "Введите ваше имя"
            width: 300
            height: 50
            font.pixelSize: 18
            anchors.horizontalCenter: parent.horizontalCenter

            // Цвет текста - черный
            color: "black"

            // Стиль placeholder (серый текст подсказки)
            placeholderTextColor: "#7f8c8d"

            background: Rectangle {
                color: "white"
                radius: 8
                border.color: "#3498db"
                border.width: 2
            }
        }

        // Кнопка
        Button {
            text: "Приветствовать"
            width: 200
            height: 50
            font.pixelSize: 16
            anchors.horizontalCenter: parent.horizontalCenter

            background: Rectangle {
                color: parent.down ? "#27ae60" :
                       parent.hovered ? "#2ecc71" : "#1abc9c"
                radius: 10
            }

            contentItem: Text {
                text: parent.text
                font: parent.font
                color: "white"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            onClicked: {
                if (nameInput.text !== "") {
                    resultText.text = "Привет, " + nameInput.text + "! 😊"
                    resultText.color = "#2ecc71"
                } else {
                    resultText.text = "Пожалуйста, введите имя!"
                    resultText.color = "#e74c3c"
                }
            }
        }

        // Результат
        Text {
            id: resultText
            color: "white"
            font.pixelSize: 20
            anchors.horizontalCenter: parent.horizontalCenter
        }

        // Анимированный элемент
        Rectangle {
            id: animatedBox
            width: 100
            height: 100
            color: "#e74c3c"
            radius: 15
            anchors.horizontalCenter: parent.horizontalCenter

            Text {
                text: "Нажми!"
                color: "white"
                anchors.centerIn: parent
                font.bold: true
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    rotationAnimation.start()
                    colorAnimation.start()
                }
            }

            // Анимация вращения
            NumberAnimation {
                id: rotationAnimation
                target: animatedBox
                property: "rotation"
                from: 0
                to: 360
                duration: 1000
                easing.type: Easing.InOutQuad
            }

            // Анимация цвета
            SequentialAnimation {
                id: colorAnimation
                ColorAnimation {
                    target: animatedBox
                    property: "color"
                    to: "#3498db"
                    duration: 500
                }
                ColorAnimation {
                    target: animatedBox
                    property: "color"
                    to: "#e74c3c"
                    duration: 500
                }
            }
        }
    }

    // Статус бар внизу
    footer: ToolBar {
        Label {
            text: "Готово к работе"
            color: "white"
            anchors.centerIn: parent
        }
        background: Rectangle {
            color: "#34495e"
        }
    }
}
