#ifndef FOOD_ORDER_H
# define FOOD_ORDER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

typedef enum OrderStatus
{
	CONFIRMATION,
	PREORDER
}	OrderStatus;
	

typedef struct	OrderRequest
{
	char				*request_nbr;		// Unique order number
	char				**food_item;		// Array of food items to order
	int					*quantity;			// Array of quantities for each food item
	char				*delivery_address;	// Delivery address for the order
	struct OrderRequest	*next;				// Pointer to the next order in the queue
}	OrderRequest;

typedef struct	OrderConfirmation
{
	char		*confirmation_nbr;	// Unique confirmation number
	char		**food_item;		// Array of food items confirmed
	int			*quantity;			// Array of quantities for each food item
	char		*delivery_address;	// Delivery address for the order
	OrderStatus	status;				// Status of the order (CONFIRMATION or PREORDER)
}	OrderConfirmation;

int							check_restaurant_status(struct OrderRequest *request);
struct OrderConfirmation	*create_standard_confirmation(void);
struct OrderConfirmation	*create_preorder_confirmation(void);
void						send_confirmation_notification(struct OrderConfirmation *confirmation);

int							process_food_order(struct OrderRequest *request);

#endif