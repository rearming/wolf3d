#include "wolf3d.h"

void    draw_items(t_wolf *wolf)
{
    int     i;
    double  x;
    double  y;
    t_ray   ray;
    double	atan_item;

    while (i < wolf->map.items_nbr)
    {
        x = wolf->map.items[i].x - wolf->player.x;
        y = wolf->map.items[i].y - wolf->player.y;
        atan_item = atan2(y, x);
        if (atan_item < 0)
            atan_item += 2 * M_PI;
        ray = raycast(wolf, atan_item);
        if (ray.distance > sqrt(x * x + y * y))
        {
            render_columns(wolf);
            draw_item(wolf, i);
        }
        else
        {
            draw_item(wolf, i);
            render_columns(wolf);
        }
        i++;
    }

}

//void 	draw_items(t_wolf *wolf)
//{
//	int i;
//
//	i = 0;
//	while (i < wolf->map.items_nbr)
//	{
//		draw_item(wolf, i);
//		i++;
//	}
//}

void check_condition(t_wolf *wolf, double atan_item, double *cord, int i)
{
	double	dist;

	dist = sqrt(cord[0] * cord[0] + cord[1] * cord[1]) * 0.25;
	if (dist < 0.1)
	{
		wolf->map.int_map[wolf->map.items[i].y][wolf->map.items[i].x] = 0;
		wolf->map.items[i].x = 0;
	}
	// dist = 1;
	scaled_draw(wolf->sdl, *wolf->textures.weapons[WEAPONS_NUM - 1].sprite,
				0.75 / dist, (t_point)
				{(atan_item - wolf->player.angle + wolf->player.fov * 0.5) * 180 / M_PI * 22 -
				(*wolf->textures.weapons[WEAPONS_NUM - 1].sprite).width * 0.75 / dist * 0.5, WIN_HEIGHT * 0.55 - dist * 4});
}

void	draw_item(t_wolf *wolf, int i)
{
	double	cord[2];
	//double	x;
	//double	y;
	double	atan_item;

	if (wolf->map.items[i].x == 0)
		return ;
	cord[0] = wolf->map.items[i].x - wolf->player.x;
	cord[1] = wolf->map.items[i].y - wolf->player.y;
	atan_item = atan2(cord[1], cord[0]);
	if (atan_item < 0)
		atan_item += 2 * M_PI;
//	ray = raycast(wolf, atan_item);
//	if (ray.distance <= sqrt(x * x + y * y))
//		return ;
	while (wolf->player.angle - wolf->player.fov < 0)
		wolf->player.angle += M_PI * 2;
	while (wolf->player.angle >= M_PI * 2)
		wolf->player.angle -= M_PI * 2;
	if (atan_item <= wolf->player.angle + wolf->player.fov / 2 &&
		atan_item >= wolf->player.angle - wolf->player.fov / 2)
		check_condition(wolf, atan_item, cord, i);
	else if (wolf->player.angle + wolf->player.fov * 0.5 > M_PI * 2)
	{
		wolf->player.angle -= 2 * M_PI;
		if (atan_item >= wolf->player.angle - wolf->player.fov * 0.5 &&
			atan_item <= wolf->player.angle + wolf->player.fov * 0.5)
			check_condition(wolf, atan_item, cord, i);
	}
	else if (atan_item + wolf->player.fov * 0.5 > 2 * M_PI)
	{
		atan_item -= 2 * M_PI;
		if (atan_item >= wolf->player.angle - wolf->player.fov * 0.5 &&
			atan_item <= wolf->player.angle + wolf->player.fov * 0.5)
			check_condition(wolf, atan_item, cord, i);
	}
}
