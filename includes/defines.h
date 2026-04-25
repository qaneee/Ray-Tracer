/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 20:07:21 by arvardan          #+#    #+#             */
/*   Updated: 2026/04/25 20:12:19 by arvardan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

# define EPS 1e-3
# define STEP 2.0f
# define ROTATE_STEP 5.0f
# define RESIZE_STEP 0.5f
# define REFLECTION_DEPTH 5
# define CHECKER_SCALE 6.000001f
# define M_PI 3.14159265358979323846

# define KEY_ESC 65307

// Error messages
# define ERR_VALID_VEC "Vector validation failed!\n"
# define ERR_POS_DIAMETER "Diameter has to be positive!\n"
# define ERR_POS_HEIGHT "Height has to be positive!\n"
# define ERR_NORM_AXIS "Axis must be normalized!\n"

// up, down, left, right, forward, backward
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_Q 113
# define KEY_E 101

// next, previous
# define KEY_N 110
# define KEY_P 112

// mode
# define KEY_C 99
# define KEY_O 111
# define KEY_L 108

// arrow keys -> same as wasd
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

// rotations
# define KEY_R 114 // x-axis pos
# define KEY_F 102 // x-axis neg
# define KEY_T 116 // y-axis pos
# define KEY_G 103 // y-axis neg
# define KEY_Y 121 // z-axis pos
# define KEY_H 104 // z-axis neg

// object property resizing
# define KEY_I 105 // cyl height +
# define KEY_K 107 // cyl height -
# define KEY_V 118 // diameter +
# define KEY_M 109 // diameter -

#endif
