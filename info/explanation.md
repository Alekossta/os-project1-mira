# Αρκετη εξηγηση υπαρχει ηδη στην μορφη comments στον κωδικα

## Εξηγηση για καθε αρχειο

BytesCounter = απλα ενα global counter για να μετραω τα bytes
CommandHandler = ειναι υπευθυνο για να παιρνει ενα command και να κανει κατι με βαση αυτο
EdgeTransaction = εχει ενα struct που αναπαριστα τα edges/transactions στον γραφο και functions για αυτα
Graph = struct για τον γραφο και functions για αυτον
NodeAccount = εχει ενα struct που αναπαριστα τα nodes/accounts στον γραφο
Prompt = ειναι υπευθυνο να εμφανιζει το prompt και να ζηταει ενα command και να το επιστρεφει και να το περναει στην main και μετα στον command handler

## Γραφος

Ο γραφος αποθηκευει ολα τα nodes σε ενα hash map. Η αναζητηση γινεται για ενα node account γινεται με O(1).
Η υλοποιηση του γραφου γινεται με seperate chaining. Επειτα σε καθε node αποθηκευουμε ενα linked list απο edges. Σε καθε node αποθηκευουμε και τα ingoing και τα outgoing edges.

Οι αλγοριθμοι για circles,traceflows,path finding,  χρησιμοποιουν DFS ή παραλλαγες αυτού με πολυπλοκότητα O(V+E) οπου V=accounts και E=transactions.

## Γενικα

σε οποιο αλγοριθμο συνανταμε linked list περιοριζομαστε αναγκαστικα σε O(n)