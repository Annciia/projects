using OrganizerNotatek.Infrastructure.DTO;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OrganizerNotatek.Infrastructure.Services
{
    public interface INoteService
    {
        NoteDTO Get(Guid Id);
        IEnumerable<NoteDTO> GetAll();
        NoteDTO Create(Guid Id, string title, string content);
        NoteDTO Update(Guid Id, string title, string content);
        void Delete(Guid Id);
    }
}
