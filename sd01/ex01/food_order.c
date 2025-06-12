#include "food_order.h"

/*
*
*	Checks if the restaurant is open based on the order. Returns 1 if open, 0 if closed.
*	int check_restaurant_status(struct OrderRequest *request);
*
*	Creates a confirmation for an immediate order. Returns NULL on failure.
*	struct OrderConfirmation *create_standard_confirmation(void);
*
*	Creates a confirmation for a future (pre-order). Returns NULL on failure.
*	struct OrderConfirmation *create_preorder_confirmation(void);
*
*	Sends the confirmation to the user.
*	void send_confirmation_notification(struct OrderConfirmation *confirmation);
*
*/

int	process_food_order(struct OrderRequest *request)
{
	struct OrderConfirmation	*confirmation;

	for (struct new_order = request; new_order; new_order = new_order->next)
	{
		if (check_restaurant_status(request))
		{
			confirmation = create_standard_confirmation();
			if (confirmation == NULL)
			{
				printf("System error, please try again later.\n");
				return (0);
			}
		}
		else
		{
			confirmation = create_preorder_confirmation();
			if (confirmation == NULL)
			{
				printf("System error, please try again later.\n");
				return (0);
			}
		}
		send_confirmation_notification(confirmation);
	}
	return (1);
}
