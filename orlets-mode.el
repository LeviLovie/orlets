(defconst orlets-mode-syntax-table
  (with-syntax-table (copy-syntax-table)
    ;; C/C++ style comments
    (modify-syntax-entry ?/ ". 124b")
    (modify-syntax-entry ?* ". 23")
    (modify-syntax-entry ?\n "> b")
    ;; Chars are the same as strings
    (modify-syntax-entry ?' "\"")
    (syntax-table))
  "Syntax table for `orlets-mode'.")

(eval-and-compile
  (defconst orlets-keywords
    '("endl" "if" "endif" "else" "swp" "lswp" "dup" "jeg" "jmp")))

(defconst orlets-highlights
  `((,(regexp-opt orlets-keywords 'symbols) . font-lock-keyword-face)
    (,(rx "(" (group-n 1 (zero-or-more (not (any "()")))) ")")
     (1 font-lock-function-name-face))))

;;;###autoload
(define-derived-mode orlets-mode prog-mode "orlets"
  "Major Mode for editing Orlets source code."
  :syntax-table orlets-mode-syntax-table
  (setq font-lock-defaults '(orlets-highlights))
  (setq-local comment-start "// "))

;;;###autoload
(add-to-list 'auto-mode-alist '("\\.orlets\\'" . orlets-mode))

(provide 'orlets-mode)

;;; orlets-mode.el ends here
