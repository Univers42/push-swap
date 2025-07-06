#include "ps.h"

/**
 * @note RULES OF THUMB, if we need to modify the pointer variable that was passed in
 * , meaning making it point somehwere else, we use double pointer. 
 * If we just need to access modify waht it points to, use single pointer
 */
static void swap(t_list *source, int size_src)
{
    t_list *temp;

    if (!source || !source->next || size_src == 0)
        return ;
    temp = source->content;
    source->content = source->next->content;
    source->next->content = temp;
}

void sa(t_ps *ps)
{
    swap(ps->stack_a, ps->size_a);
    
    if (is_recording())
        record_operation("sa");
    else
        ft_printf("sa\n");
}

void sb(t_ps *ps)
{
    swap(ps->stack_b, ps->size_b);
    
    if (is_recording())
        record_operation("sb");
    else
        ft_printf("sb\n");
}

void ss(t_ps *ps)
{
    swap(ps->stack_a, ps->size_a);
    swap(ps->stack_b, ps->size_b);
    
    if (is_recording())
        record_operation("ss");
    else
        ft_printf("ss\n");
}