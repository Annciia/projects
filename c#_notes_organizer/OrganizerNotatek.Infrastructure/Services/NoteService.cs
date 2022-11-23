using OrganizerNotatek.Core.Domain;
using OrganizerNotatek.Core.Repositories;
using OrganizerNotatek.Infrastructure.DTO;
using OrganizerNotatek.Infrastructure.Repositories;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OrganizerNotatek.Infrastructure.Services
{
    public class NoteService : INoteService
    {
        private readonly INoteRepository _noteRepository;
        public NoteService(INoteRepository noteRepository)
        {
            _noteRepository = noteRepository;
        }
        public NoteDTO Get(Guid Id)
        {
            var note = _noteRepository.Get(Id);

            if (note == null)
            {
                return null;
            }

            NoteDTO notedto= new NoteDTO()
            {
                Id = note.Id.ToString(),
                Title = note.Title,
                Content = note.Content
            };
            return notedto;
        }

        public IEnumerable<NoteDTO> GetAll()
        {
            var notes = _noteRepository.GetAll();

            return notes.Select(notes => new NoteDTO
            {
                Id = notes.Id.ToString(),
                Title = notes.Title,
                Content = notes.Content
            }); 
        }

        public NoteDTO Create(Guid Id, string title, string content)
        {
            var note = new Note(Id, title, content);
            _noteRepository.Add(note);
            return new NoteDTO()
            {
                Id = note.Id.ToString(),
                Title = note.Title,
                Content = note.Content
            };
        }

        public NoteDTO Update(Guid Id, string title, string content)
        {
            var note = _noteRepository.Get(Id);
            if (note == null)
            {
                return null;
            }
            note.SetTitle(title);
            note.SetContent(content);
            _noteRepository.Update(note);

            return new NoteDTO()
            {
                Id = note.Id.ToString(),
                Title = note.Title,
                Content = note.Content
            };
        }

        public void Delete(Guid Id)
        {
            var note = _noteRepository.Get(Id);
            _noteRepository.Delete(note);
        }
    }
}
