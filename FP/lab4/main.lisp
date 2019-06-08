(defun whitespace-char-p (char)
  (member char '(#\Space #\Tab #\Newline)))

(defun russian-lower-case-p (char)
  (position char "абвгдеёжзиклмнопрстуфхцчшщъыьэюя"))

(defun text-processing (text)
    (loop for sentence in text
        collect (concat-string (sentence-processing sentence))))

(defun sentence-processing (string)
    (loop with len = (length string)
        for left = 0 then (or (position-if-not #'whitespace-char-p string :start right) len)
        for right = (or (position-if #'whitespace-char-p string :start left) len)

        if (or (some #'lower-case-p (subseq string left right)) 
               (some #'russian-lower-case-p (subseq string left right)))
            collect (concatenate 'string (subseq string left right) ",")
        if (not (or (some #'lower-case-p (subseq string left right)) 
                    (some #'russian-lower-case-p (subseq string left right))))
            collect (subseq string left right)

        collect (subseq string right 
            (or (position-if-not #'whitespace-char-p string :start right) len))
        
        while (< right len)))

(defun concat-string (list)
  "A non-recursive function that concatenates a list of strings."
  (if (listp list)
      (let ((result ""))
        (dolist (item list)
          (if (stringp item)
              (setq result (concatenate 'string result item))))
        result)))