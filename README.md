# songlist
 Нужно реализовать таблицу, в которой отображается список музыкальных

 композиций. Колонки в таблице следующие:
    • Превью альбома;
    • Название (название песни);
    • Исполнитель;
    • Продолжительность (продолжительность песни);
В первой колонке отображается изображение.
Справа от таблицы должны находиться кнопки “Создать”, “Редактировать”,
“Сохранить”. Кoмпозицию можно добавить в список, нажав кнопку «Создать».
По нажатию Ok, созданная композиция попадает в таблицу.
Для редактирования данных о песне нужно выделить строку таблицы и нажать
“Редактировать”. Снова открывается окно с данными о песне, пользователь
может их откорректировать.При нажатии «Сохранить» происходит сохранение
данных таблицы в любом удобном формате. При повторном запуске программы
данные должны считаться и отобразиться (таблица будет выглядеть так же,
как до закрытия).
При наведении курсора на строку таблицы возникает подсказка (QToolTip) с
оценкой композиции (текст подсказки “Оценка: 5”, “Оценка: 4” – см.
SongDialog). Добавлена кнопка “Сортировать”, после нажатия которой
происходит сортировка песен в таблице.
