{
  _id: ObjectId('652f4d1e2f4b3c1a9c1e4c1c'),
  type: 'sender',
  contact_person: {
    first_name: 'Петр',
    last_name: 'Петров'
  },
  name: 'ООО Ромашка',
  parcels: {
    _id: ObjectId('652f4d1e2f4b3c1a9c1e4b6a'),
    tracking_id: 'ABC123',
    recipient_id: ObjectId('652f4d1e2f4b3c1a9c1e4c1a'),
    sender_id: ObjectId('652f4d1e2f4b3c1a9c1e4c1c'),
    parcel_info: {
      weight: 5.2,
      cost: 1200
    },
    delivery: {
      address_id: ObjectId('652f4d1e2f4b3c1a9c1e4c1b'),
      contact_person: {
        first_name: 'Сергей',
        last_name: 'Сергеев'
      },
      desired_time_range: '10:00-14:00',
      actual_delivery_date: 2024-02-15T12:30:00.000Z,
      delivered: true
    },
    shipment_date: 2024-02-15T00:00:00.000Z,
    recipient: [
      {
        _id: ObjectId('652f4d1e2f4b3c1a9c1e4c1a'),
        type: 'recipient',
        name: {
          first_name: 'Иван',
          last_name: 'Иванов'
        },
        contact_person: null,
        address_ids: [
          ObjectId('652f4d1e2f4b3c1a9c1e4c1b')
        ]
      }
    ]
  }
}