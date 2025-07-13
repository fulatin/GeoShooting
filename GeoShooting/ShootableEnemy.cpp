#include "ShootableEnemy.h"
#include "GlobalVal.h"
#include "SoundManager.h"
#include "constants.h"
using namespace GeoShooting;
ShootableEnemy::ShootableEnemy(float x, float y, float width, float height, Vector direction, float speed, Player* _target)
	: Enemy(x, y, width, height, direction, speed, _target) {
	// 初始化射击敌人的属性
	shootInterval = 2.0f; // 射击间隔时间
	lastShootTime = 0.0f; // 上次射击时间
	bulletSpeed = 800.0f+gameTime; // 子弹速度
	bulletDamage = 5.0f+gameTime/10; // 子弹伤害
	enemyColor = RGB(255, 165, 0); // 射击敌人颜色

}
void ShootableEnemy::update() {
	// 更新射击敌人状态
	Enemy::update(); // 调用基类的更新方法
	// 检查是否可以射击
	if (gameTime - lastShootTime >= shootInterval&&!isOffScreen()) {
		shoot(); // 射击
		lastShootTime = gameTime; // 更新上次射击时间
	}

}
void ShootableEnemy::draw() {
	// 绘制射击敌人
	Enemy::draw(); // 调用基类的绘制方法

	// 画一个指向玩家的等边小三角形
	Vector playerPosition = targetPlayer->getPosition(); // 获取玩家位置
	Vector directionToPlayer = playerPosition - Vector(x, y); // 计算指向玩家的方向
	directionToPlayer.normalize(); // 确保方向是单位向量
	float triangleSize = 10.0f; // 三角形大小
	int offset = max(width, height); // 偏移量，确保三角形不和玩家重叠
	Vector trangleCenter = Vector(x,y)+directionToPlayer*offset; // 三角形中心位置
	Vector center2vert = directionToPlayer * triangleSize; // 三角形顶点到中心的向量

	setlinecolor(enemyColor); // 设置三角形颜色
	Vector vertex1 = center2vert + trangleCenter; // 第一个顶点
	Vector vertex2 = center2vert.rotate(2 * PI / 3) + trangleCenter; // 第二个顶点
	Vector vertex3 = center2vert.rotate(4 * PI / 3) + trangleCenter; // 第三个顶点
	line(vertex1.x, vertex1.y, vertex2.x, vertex2.y); // 绘制第一条边
	line(vertex2.x, vertex2.y, vertex3.x, vertex3.y); // 绘制第二条边
	line(vertex3.x, vertex3.y, vertex1.x, vertex1.y); // 绘制第三条边
}
void ShootableEnemy::shoot() {
	// 创建子弹并添加到游戏对象列表中
	Vector playerPosition = targetPlayer->getPosition(); // 获取玩家位置
	Vector direction = playerPosition - Vector(x, y); // 计算指向玩家的方向
	float distanceToPlayer = direction.length(); // 计算敌人与玩家之间的距离

	Vector playerSpeed = targetPlayer->speed; // 获取玩家速度
	// 根据离玩家的距离和玩家的速度计算子弹方向

	direction = direction + playerSpeed * (distanceToPlayer / bulletSpeed + 0.3 ); // 调整方向以考虑玩家的移动
	  
	direction.normalize(); // 确保方向是单位向量
	Bullet* bullet = new Bullet(x, y, 10.0f, 10.0f, direction, bulletSpeed, bulletDamage, this); // 创建子弹
	bullet->setBulletColor(RGB(255, 123, 0)); // 设置子弹颜色为红色

	bullets.insert(bullet); // 将子弹添加到游戏对象列表中


	SoundManager::getInstance().playSound(L"enemyShoot", 1000); // 播放射击音效
}