# operating_systems_cckShell

Το πρόγραμμα cckShell αποτελεί ένα απλό Shell, το οποίο αναπτύχθηκε για τα πλαίσια πανεπιστημιακής εργασίας και επομένως υποστηρίζει μόνο πολύ βασικές λειτουργίες (για την κάλυψη των ζητουμένων).
Το Shell υποστηρίζει δύο modes το interactive και το batchfile αντίστοιχα.
Στο πρώτο διαβάζεται μια γραμμή εντολών, γίνεται έλεγχος για την περίπτωση άδειας εντολής ή γραμμής καθώς και για την ύπαρξη της εντολής quit που οδηγεί σε έξοδο, και εκτελούνται οι εντολές (αφού γίνει διαχωρισμός τους αν υπάρχει ενδιάμεσα ";" ή "&").
Στο δεύτερο γίνεται έλεγχος για την ύπαρξη του αρχείου από το οποίο θα διαβαστούν οι εντολές, ανοίγει το αρχείο εφόσον υπάρχει, διαβάζονται οι εντολές της κάθε σειράς και εκτελούνται έπειτα όπως κατά αντιστοιχία με το interactive.
(Σε κάποιους συνδιασμούς υπάρχει κάποιο θέμα με τα delimeters.)
