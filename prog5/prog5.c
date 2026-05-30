#include <stdio.h>

union decision
{
    unsigned char flags;

    struct
    {
        unsigned int your_choice : 1;
        unsigned int your_mothers_choice : 1;
        unsigned int your_fathers_choice : 1;
        unsigned int socially_acceptable : 1;
        unsigned int financially_viable : 1;
        unsigned int do_you_have_aptitude : 1;
        unsigned int do_you_like_it : 1;
        unsigned int decision : 1;
    } field;
};

union decision input();
void make_decision(union decision *d);
void print_decision(union decision d);
void final_conclusion(union decision d);

int main(){
    union decision d;
    d = input();
    make_decision(&d);
    print_decision(d);
    final_conclusion(d);
    return 0;
}

union decision input()
{
    union decision d = {0};
    unsigned int temp;

    printf("Enter 1 if YES and 0 if NO\n");

    printf("Your choice: ");
    scanf("%u", &temp);
    d.field.your_choice = temp;

    printf("Your mother's choice: ");
    scanf("%u", &temp);
    d.field.your_mothers_choice = temp;

    printf("Your father's choice: ");
    scanf("%u", &temp);
    d.field.your_fathers_choice = temp;

    printf("Socially acceptable: ");
    scanf("%u", &temp);
    d.field.socially_acceptable = temp;

    printf("Financially viable: ");
    scanf("%u", &temp);
    d.field.financially_viable = temp;

    printf("Do you have aptitude: ");
    scanf("%u", &temp);
    d.field.do_you_have_aptitude = temp;

    printf("Do you like it: ");
    scanf("%u", &temp);
    d.field.do_you_like_it = temp;

    return d;
}
void make_decision(union decision *d){
    d->field.decision = d->field.your_choice && d->field.financially_viable && d->field.do_you_have_aptitude && d->field.do_you_like_it;

}

void print_decision(union decision d){
    if (d.field.decision)
            printf("Decision: Go ahead with your choice.\n");
        else
            printf("Decision: Reconsider your choice.\n");
}

void final_conclusion(union decision d){
     printf("\nFlags value = %u\n", d.flags);
    
        if (d.flags == 255)
        {
            printf("Perfect situation! Every factor is positive.\n");
        }
        else if (d.field.decision)
        {
            printf("Most important conditions are satisfied.\n");
        }
        else
        {
            printf("Some important conditions are not satisfied.\n");
        }
}