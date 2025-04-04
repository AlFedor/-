/*
 * Пример использования библиотеки MDCA для управления роботом
 * с 4 моторами и ИК-датчиком расстояния
 * 
 * Библиотека инкапсулирует управление моторами и чтение данных с датчика
 */

// Подключаем нашу библиотеку
#include <MDCA.h>

// Определяем пины подключения моторов и датчика
// (должны соответствовать реальному подключению)
#define LFF_PIN 4    // Левый передний - вперед
#define LFB_PIN 3    // Левый передний - назад
#define RFF_PIN 5    // Правый передний - вперед
#define RFB_PIN 6    // Правый передний - назад
#define LBF_PIN 10   // Левый задний - вперед
#define LBB_PIN 8    // Левый задний - назад
#define RBF_PIN 11   // Правый задний - вперед
#define RBB_PIN 12   // Правый задний - назад
#define IK_PIN A7    // Аналоговый пин ИК-датчика расстояния

// Создаем объект робота, передавая в конструктор все пины
MDCA robot(LFF_PIN, LFB_PIN, RFF_PIN, RFB_PIN, 
           LBF_PIN, LBB_PIN, RBF_PIN, RBB_PIN, 
           IK_PIN);

void setup() {
  // Инициализируем робота (настраивает пины)
  robot.begin();
  
  // Инициализируем последовательный порт для отладки
  Serial.begin(9600);
  Serial.println("Робот инициализирован, начинаем через 5 секунд...");
  
  // Пауза перед стартом (5 секунд)
  delay(5000);
}

void loop() {
  // Основной цикл управления роботом
  
  // Получаем текущее расстояние от ИК-датчика
  int distance = robot.dist_ik();
  
  // Выводим расстояние в монитор порта для отладки
  Serial.print("Расстояние: ");
  Serial.print(distance);
  Serial.println(" см");
  
  // Логика управления в зависимости от расстояния
  if (distance < 40) {
    // Если расстояние меньше 40 см - объект слишком близко
    // Двигаемся назад и немного вправо (разворот)
    Serial.println("Объект слишком близко - отступаем вправо");
    robot.go(-180, 150, -180, 150);
    
  } else if (distance > 70) {
    // Если расстояние больше 70 см - объект слишком далеко
    // Двигаемся вперед и немного влево (разворот)
    Serial.println("Объект слишком далеко - двигаемся влево");
    robot.go(150, -180, 150, -180);
    
  } else {
    // Оптимальное расстояние (40-70 см) - двигаемся прямо
    Serial.println("Оптимальное расстояние - двигаемся прямо");
    robot.go(150, 150, 150, 150);
  }
  
  // Небольшая задержка для стабильности работы
  delay(100);
}

/*
 * Дополнительные примеры использования методов библиотеки:
 * 
 * 1. Резкая остановка с торможением на 200 мс:
 *    robot.stopp(200);
 * 
 * 2. Движение вперед с одинаковой скоростью:
 *    robot.go(200, 200, 200, 200);
 * 
 * 3. Разворот на месте по часовой стрелке:
 *    robot.go(200, -200, 200, -200);
 * 
 * 4. Движение назад:
 *    robot.go(-200, -200, -200, -200);
 * 
 * 5. Получение расстояния без вывода в Serial:
 *    int dist = robot.dist_ik();
 */
