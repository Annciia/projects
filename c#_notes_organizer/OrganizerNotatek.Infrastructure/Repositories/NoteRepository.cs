using OrganizerNotatek.Core.Repositories;
using OrganizerNotatek.Core.Domain;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OrganizerNotatek.Infrastructure.Repositories
{
    public class NoteRepository : INoteRepository
    {
        private static readonly ISet<Note> _notes = new HashSet<Note>()
        {
            new Note(Guid.NewGuid(), "Tytul 1", "Tresc 1"),
            new Note(Guid.NewGuid(), "Tytul 2", "Tresc 2")
        };

        public Note Get(Guid Id)
        {
            return _notes.SingleOrDefault(x => x.Id == Id);    
        }

        public IEnumerable<Note> GetAll()
        {
            return _notes;
        }

        public Note Add(Note note)
        {
            _notes.Add(note);
            return note;
        }

        public void Update(Note note)
        {
         
        }

        public void Delete(Note note)
        {
            _notes.Remove(note);
        }


    }
}
