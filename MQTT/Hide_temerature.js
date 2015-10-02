    var devices = $('mqtt.1.Temperature*');
    function olderThanMinute(ts){
        return (new Date().getTime() - ts > 60000);
    }
    // Инициализация и создание переменных
    devices.each(function (id) {
         // Если это не наш таймер
         if (id.indexOf('_timer) == -1) {
              // И переменная timer ещё не существует
              if (!getState(id + '_timer')) {
                    // создать
                   createState(id + '_timer', !olderThanMinute(getState(id).ts));
              } else {
                   // инициализировать
                   setState(id + '_timer', !olderThanMinute(getState(id).ts));
              }
         }
    });

    //Выполнять каждую минуту
    schedule('* * * * *', function () {
         // перебор всех устройств
         devices.each(function (id) {
             // Если это не таймер
             if (id.indexOf('_timer) == -1) {
                   // обновить время
                   setState(id + '_timer', !olderThanMinute(getState(id).ts));
             }
         });
    });
