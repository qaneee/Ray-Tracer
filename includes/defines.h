/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arvardan <arvardan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 20:07:21 by arvardan          #+#    #+#             */
/*   Updated: 2026/04/25 20:29:16 by arvardan         ###   ########.fr       */
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

// Error messages
# define ERR_VALID_VEC "Vector validation failed!\n"
# define ERR_POS_DIAMETER "Diameter has to be positive!\n"
# define ERR_POS_HEIGHT "Height has to be positive!\n"
# define ERR_NORM_AXIS "Axis must be normalized!\n"

# ifdef __APPLE__

#  define KEY_ESC 53
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_Q 12
#  define KEY_E 14
#  define KEY_N 45
#  define KEY_P 35
#  define KEY_C 8
#  define KEY_O 31
#  define KEY_L 37
#  define KEY_UP 126
#  define KEY_DOWN 125
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_R 15
#  define KEY_F 3
#  define KEY_T 17
#  define KEY_G 5
#  define KEY_Y 16
#  define KEY_H 4
#  define KEY_I 34
#  define KEY_K 40
#  define KEY_V 9
#  define KEY_M 46
# else

// Linux
#  define KEY_ESC 65307
#  define KEY_W 119
#  define KEY_A 97
#  define KEY_S 115
#  define KEY_D 100
#  define KEY_Q 113
#  define KEY_E 101
#  define KEY_N 110
#  define KEY_P 112
#  define KEY_C 99
#  define KEY_O 111
#  define KEY_L 108
#  define KEY_UP 65362
#  define KEY_DOWN 65364
#  define KEY_LEFT 65361
#  define KEY_RIGHT 65363
#  define KEY_R 114
#  define KEY_F 102
#  define KEY_T 116
#  define KEY_G 103
#  define KEY_Y 121
#  define KEY_H 104
#  define KEY_I 105
#  define KEY_K 107
#  define KEY_V 118
#  define KEY_M 109
# endif

#endif