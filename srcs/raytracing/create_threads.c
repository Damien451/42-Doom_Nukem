/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 09:37:40 by roduquen          #+#    #+#             */
/*   Updated: 2019/11/10 09:42:55 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int						raytracing(t_doom *data)
{
	t_thread		thread[NBR_THREAD];
	int				i;

	i = 0;
	data->light.power = 50 + (rand() & 255);
	data->light.power = 50;
	if (data->ball)
		light_gun(data);
	SDL_RenderClear(data->lib.renderer);
	if (!data->lib.cam_keys && data->sampling != 1)
		data->sampling = 1;
	data->sampling = 6;
	while (i < NBR_THREAD)
	{
		thread[i].data = data;
		thread[i].image = data->lib.image;
		thread[i].num = data->sampling * (i);
		thread[i].frame = i;
		thread[i].total_frame = i;
		if (pthread_create(&thread[i].thread, NULL, (*launch_rays)
			, &thread[i]) < 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < NBR_THREAD)
		pthread_join(thread[i++].thread, NULL);
	return (0);
}
